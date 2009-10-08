/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include <os.h>
#include <TableConfig.h>
#include <SessionImpl.h>
#include <SqlFactory.h>
#include <AbsSqlConnection.h>
#include <AbsSqlStatement.h>
#include <SqlNwConnection.h>
#include <SqlOdbcConnection.h>
#include <SqlNwStatement.h>
#include <SqlConnection.h>
#include <SqlStatement.h>
#include <SqlFactory.h>
#include <CSql.h>
#include <Network.h>
#include <SqlLogStatement.h> //for BindSqlField
#include <SqlNetworkHandler.h>

class AbsCSqlQIterator
{
    public:
    virtual void *next() = 0;
};

class AbsCSqlQueue
{
    public:
    virtual void push(void *log, int len) = 0;
    virtual void pop() = 0;
    virtual int size() = 0;
};

class ListIter : public AbsCSqlQIterator
{
    public:
    ListIterator iter;
    ListIter(List &list) { iter = list.getIterator(); }
    void *next() { return iter.nextElementInQueue(); }
};

typedef struct FailedStmtObject {
    int stmtId;
    DbRetVal eType;
} FailStmt;


long long qIndex = 0;

class ListAsQueue : public AbsCSqlQueue
{
    public:
    List list;
    ListAsQueue() {}
    void push(void *log, int len) 
    {
        int logSize = sizeof(long long) + len + sizeof(int) + sizeof(long);
        char *logElem = (char *) malloc(os::align(logSize));
        *(long long *) logElem = ++qIndex;
        *(int*)(logElem + sizeof(long long))= len;
        char *ptr = logElem + sizeof(int) + sizeof(long long);
        memcpy(ptr, log, len+sizeof(long)); //long for msg type
        list.append(logElem);
        printDebug(DM_ReplServer, "Pushed Element: %x", logElem);
    }
    int size() { return list.size(); }
    void pop(){};
};


class ThreadInputData
{
    public:
    AbsCSqlQIterator *qIter;
    long long *indexPtr;
    ThreadInputData() { qIter = NULL; indexPtr = NULL; }
};

void *startThread(void *p);


void printUsage()
{
   printf("Usage: csqlasyncserver \n");
   printf("Description: Start the csql Async server.\n");
   return;
}

DbRetVal processMessage(void *str, int len, void *conn, void *hashBucketPtr,
                   SqlApiImplType flag, List *prepareFailList);
void *freeMsgFromQueue(void *p);
DbRetVal handlePrepare(void *str, void *conn, void *stmtBuckets,
                                   SqlApiImplType flag, List *prepareFailList);
DbRetVal handleCommit(void *str, int len, void *conn, void *stmtBuckets,
                                         List *prepareFailList);
DbRetVal handleFree(void *str, void *stmtBuckets, List *prepareFailList);
AbsSqlStatement *getStmtFromHashTable(int stmtId, void *stmtBuckets);
DbRetVal writeToConfResFile(void *data, int len, void *stmtBuckets, 
                                                    char *dsn);

int getHashBucket(int stmtid)
{
    return (stmtid % STMT_BUCKET_SIZE);
}

AbsCSqlQueue *csqlQ = NULL;

int srvStop =0;
int msgKey = 0;

ThreadInputData **thrInput;


int asyncSites = 0;
int syncSites = 0;
long long * indexCountPtr = NULL;
pthread_t freeThrId = 0;

static void sigTermHandler(int sig)
{
    printf("Received signal %d\nStopping the server\n", sig);
    os::msgctl(msgKey, IPC_RMID, NULL); 
    srvStop = 1;
}

int main(int argc, char **argv)
{
    int c = 0, opt = 0;
    while ((c = getopt(argc, argv, "?")) != EOF) {
        switch (c) {
            case '?' : { opt = 10; break; } //print help 
            default: opt=10; 
        }
    }//while options
    if (opt == 10) { printUsage();
        return 0;
    }

    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);

    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    if (( !Conf::config.useCache() && 
            Conf::config.getCacheMode() == SYNC_MODE) ) {
        printf("Replication server not started\n");
        return 1;
    } 

    bool found =false;
    //printf("config id = %d\n", Conf::config.getSiteID()); 
    
    if ((!Conf::config.useCache() && 
          Conf::config.getCacheMode()==SYNC_MODE)) {
        printf("There are no async sites\n");
        return 4;
    }

    msgKey = os::msgget(Conf::config.getMsgKey(), 0666);
    if (msgKey == -1) {
        printf("Message Queue creation failed\n");
        return 4;
    }

    csqlQ = new ListAsQueue();
    ListIterator itr = ((ListAsQueue *)csqlQ)->list.getIterator(); 
    
    if (Conf::config.useCache() && Conf::config.getCacheMode()==ASYNC_MODE) {
        asyncSites++;
    }
    pthread_t *thrId =new pthread_t [asyncSites];
    thrInput = (ThreadInputData **) malloc(sizeof(ThreadInputData *) * asyncSites);
    indexCountPtr = (long long *) malloc(sizeof(long long) * asyncSites);
    memset(indexCountPtr, 0, sizeof(long long) * asyncSites);
    int i=0;
    if(Conf::config.useCache() && Conf::config.getCacheMode()==ASYNC_MODE) {
        thrInput[i] = new ThreadInputData();
        thrInput[i]->qIter = NULL;
        thrInput[i]->indexPtr = &indexCountPtr[i];
        pthread_create(&thrId[i], NULL, &startThread, thrInput[i]);
        i++;
    } 
    pthread_create(&freeThrId, NULL, freeMsgFromQueue, NULL);
    struct timeval timeout, tval;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int msgSize = Conf::config.getAsyncMsgMax();
    char str[8192];
   // printf("Replication Server Started");
    while (!srvStop) {
        tval.tv_sec = timeout.tv_sec;
        tval.tv_usec = timeout.tv_usec;
        os::select(0, 0, 0, 0, &tval);
        printDebug(DM_ReplServer, "waiting for message");
        while(true) {
           long size = os::msgrcv(msgKey, str, msgSize, 0, 0666|IPC_NOWAIT);// process logs
           printDebug(DM_ReplServer, "Received msg size = %d", size);
           if (size == -1 || srvStop) break;
           csqlQ->push(str, size); // long for mtype of msg  
        }
    }
    delete[] thrId;
    printf("Replication Server Exiting\n");
    return 0;
}

void *startThread(void *thrInfo)
{
    DbRetVal rv = OK;
    ThreadInputData *thrInput = (ThreadInputData *)thrInfo;
    List prepareFailList;
    SqlApiImplType flag;
    flag = CSqlAdapter;
    printDebug(DM_ReplServer, "SqlAdapter Thread created");
    AbsCSqlQIterator *iter = thrInput->qIter;
    while (1) { if (csqlQ->size()) break; }
    iter = new ListIter(((ListAsQueue *)csqlQ)->list);
    AbsSqlConnection *conn = SqlFactory::createConnection(flag);
    void *stmtBuckets = malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    memset(stmtBuckets, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));
    printDebug(DM_ReplServer, "stmtbuckets: %x", stmtBuckets);
    struct timeval timeout, tval;
    timeout.tv_sec = 0;
    while (1) {
        while (1) {
            rv = conn->connect(I_USER, I_PASS);
            if (rv == OK) break;
            printError(rv, "Unable to connect to peer site");
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;
            os::select(0, 0, 0, 0, &timeout);
        }
        while (1) {
            void *msg = NULL;
            while (1) {
                msg = iter->next(); //receive msg from csqlQ
                if (msg != NULL) break;
                tval.tv_sec = 5;
                tval.tv_usec = 1000;
                os::select(0, 0, 0, 0, &tval);
            }
            long long index = *(long long *) msg;
            int length = *(int *)((char *)msg+sizeof(long long));             
            char *msgptr = (char *)msg + sizeof(long long) + sizeof(int);
            printDebug(DM_ReplServer, "entering process message");
            rv = processMessage(msgptr, length, conn, stmtBuckets, flag, 
                                                             &prepareFailList);
            if (rv == ErrNoConnection) break;
            printDebug(DM_ReplServer, "processed message");
            *(long long *) thrInput->indexPtr = index;
            printDebug(DM_ReplServer, "index %d is stored in Main index log array\n", index);
        }
    }
    return NULL;
}

DbRetVal processMessage(void *str, int len, void *conn, void *stmtBuckets,
                    SqlApiImplType flag, List *prepareFailList)
{
    long type = *(long *) str;
    printDebug(DM_ReplServer, "type = %d\n", type);
    char *data = (char *) str + sizeof(long);
    if (type == 1) return handlePrepare(data, conn, stmtBuckets, flag, 
                                                              prepareFailList);
    else if (type == 2) return handleCommit(data, len, conn, stmtBuckets, 
                                                    prepareFailList);
    else if (type == 3) return handleFree(data, stmtBuckets, prepareFailList);
}

void *freeMsgFromQueue(void *indCntPtr)
{
    long long minIndex = 0;
    struct timeval timeout, tval;
    timeout.tv_sec = 0;
    printDebug(DM_ReplServer, "waiting for free the q elements");
    while(1) {
        if (csqlQ->size()) break;
///        printError(ErrWarning, "List is empty");
        tval.tv_sec = 1;
        tval.tv_usec = 1000;
        os::select(0, 0, 0, 0, &tval);
    }
    AbsCSqlQIterator *iter = new ListIter(((ListAsQueue *)csqlQ)->list);
    while (1) {
        minIndex = indexCountPtr[0];
        for (int i=0; i < asyncSites; i++) {
            if (minIndex > indexCountPtr[i]) minIndex = indexCountPtr[i];
        }
        void *msg = NULL;
        while (1) {
            msg = iter->next(); //receive msg from csqlQ
            if (msg == NULL) break;
            if( *(long long *) msg <= minIndex) {
                long long num = *(long long *) msg;
                free (msg); msg = NULL;
            } else break;
        }
        tval.tv_sec = 0;
        tval.tv_usec = 100000;
        os::select(0, 0, 0, 0, &tval);
    }
    return NULL;
}

DbRetVal handlePrepare(void *data, void *conn, void *stmtBuckets,
                                   SqlApiImplType flag, List *prepareFailList)
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = (AbsSqlConnection *)conn;
    AbsSqlStatement *stmt = SqlFactory::createStatement(flag);
    stmt->setConnection(con);
    char *ptr = (char *) data;
    int length = *(int *) ptr; ptr += sizeof(int);
    int txnId = *(int *) ptr; ptr += sizeof(int);
    int stmtId = *(int *) ptr; ptr += sizeof(int);
    char *tblName = ptr; ptr += IDENTIFIER_LENGTH;
    char *stmtstr = (char *)data + 3 * sizeof(int) + IDENTIFIER_LENGTH;
    int i = 1;

    unsigned int mode = TableConf::config.getTableMode(tblName);
    bool isCached = TableConf::config.isTableCached(mode);

    if ((flag == CSqlAdapter) && !isCached) {
        FailStmt *fst = new FailStmt();
        fst->stmtId = stmtId;
        fst->eType = ErrNotCached;
        prepareFailList->append(fst);
        return OK;
    }

    printDebug(DM_ReplServer, "stmt str: %s", stmtstr);
    rv = stmt->prepare(stmtstr);
    if (rv != OK) { 
        FailStmt *fst = new FailStmt();
        fst->stmtId = stmtId;
        fst->eType = rv;
        prepareFailList->append(fst);
        return rv;
    }
    int bucketNo = getHashBucket(stmtId);
    printDebug(DM_ReplServer, "PrepHdl: stmtBuckets: %x", stmtBuckets);
    printDebug(DM_ReplServer, "PrepHdl: bucketno: %d", bucketNo);
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    printDebug(DM_ReplServer, "PrepHdl: bucket addr: %x", stmtBucket);
    StmtNode *node = new StmtNode();
    printDebug(DM_ReplServer, "PredHdl: stmtNode addr: %x", node);
    node->stmtId = stmtId;
    node->stmt = stmt;
    strcpy(node->stmtstr, stmtstr);
    printDebug(DM_ReplServer, "PrepHdl: stmt id: %d stmt %x", node->stmtId, node->stmt);
    stmtBucket->bucketList.append(node);
    
    printDebug(DM_ReplServer, "returning from prepare");
    return rv;
}; 

DbRetVal handleCommit(void *data, int len, void *conn, void *stmtBuckets, 
                                         List *prepareFailList)
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = (AbsSqlConnection *)conn;
    // get dsn if adapter to write into conflict resolution file
    char *dsn = NULL;
    SqlOdbcConnection *adCon = (SqlOdbcConnection *) con;
    dsn = adCon->dsn;
    char *ptr = (char *) data; 
    int datalen = *(int *) ptr; ptr += sizeof(int);
    int txnId = *(int *) ptr; ptr += sizeof(int); 
    FailStmt *elem = NULL;
    rv = con->beginTrans();
    if (rv != OK) { 
        printError(rv, "Begin trans failed"); 
        return rv;
    } 
    while ((ptr - (char *)data) < len) {
        int stmtId = *(int *)ptr;
        ptr += sizeof(int);
        AbsSqlStatement *stmt = getStmtFromHashTable(stmtId, stmtBuckets);
        printDebug(DM_ReplServer, "commit: stmtId: %d", stmtId);
        printDebug(DM_ReplServer, "commit: stmtbuckets: %x", stmtBuckets);
        printDebug(DM_ReplServer, "commit: stmt: %x", stmt);
        ExecType type = (ExecType) (*(int *) ptr);
        ptr += sizeof(int);
        if (type == SETPARAM) {
            int parampos = *(int *) ptr;
            ptr += sizeof(int);
            DataType dataType = (DataType) ( *(int *) ptr);
            ptr += sizeof(int);
            int length = *(int *) ptr;
            ptr += sizeof(int);
            void *value = ptr; 
            ptr += length;
            if (stmt != NULL) 
                SqlNetworkHandler::setParamValues(stmt, parampos, dataType, 
                                                        length, (char *)value);
        } else {
            // start executing and committing for all active connections
            int rows;
            if (stmt != NULL) rv = stmt->execute(rows);
            if (rv != OK) { 
                printError(rv, "Execute failed with return value %d", rv); 
                if (rv == ErrNoConnection) return rv;
                else {
                    // write to conflict resolution file  
                    writeToConfResFile(data, len, stmtBuckets, dsn);
                    con->rollback();
                    return OK;
                }
            }
            if (stmt == NULL) {
                ListIterator it = prepareFailList->getIterator();
                bool found = false;
                while (it.hasElement()) {
                    elem = (FailStmt *) it.nextElement();
                    if (elem->stmtId == stmtId) { found = true; break; }
                }
                if (! found) continue; // for local table
                if ((elem->eType == ErrNotCached) || 
                     elem->eType == ErrNotExists) 
                    continue;
                else {
                    // write to conflict resolution file  
                    writeToConfResFile(data, len, stmtBuckets, dsn);
                    con->rollback();
                    return OK;
                }
            }
        }
    }
    rv = con->commit();
    if (rv != OK) { printDebug(DM_ReplServer, "commit failed"); }
    else { printDebug(DM_ReplServer, "commit passed"); }
    return OK;
}

DbRetVal handleFree(void *data, void *stmtBuckets, List *prepareFailList)
{
    DbRetVal rv = OK;
    char *ptr = (char *) data;
    int len = *(int *) ptr; ptr += sizeof(int);
    int txnId = *(int *) ptr; ptr += sizeof(int);
    int stmtId = *(int *)ptr;
    AbsSqlStatement *stmt = getStmtFromHashTable(stmtId, stmtBuckets);
    FailStmt *elem = NULL;
    if (stmt == NULL) {
        ListIterator failListIter = prepareFailList->getIterator();
        while (failListIter.hasElement()) {
            elem = (FailStmt *) failListIter.nextElement();
            if (elem->stmtId == stmtId) break;
        }
        failListIter.reset();
        prepareFailList->remove(elem);
        return OK;
    }
    rv = stmt->free();
    if (rv != OK) {
        printError(rv, "HandleFree failed with return vlaue %d", rv);
        return rv;
    }
    int bucketNo = getHashBucket(stmtId);
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtId == node->stmtId) break;
    }
    it.reset(); 
    printDebug(DM_ReplServer, "GSFHT: node: %x", node);
    printDebug(DM_ReplServer, "GSFHT: stmtId: %d", node->stmtId);
    printDebug(DM_ReplServer, "GSFHT stmt: %x", node->stmt);
    stmtBucket->bucketList.remove(node);
    if (node->stmt) delete stmt;
    delete node; node = NULL;
    return OK;
}

AbsSqlStatement *getStmtFromHashTable(int stmtId, void *stmtBuckets)
{
    int bucketNo = getHashBucket(stmtId);
    printDebug(DM_ReplServer, "GSFHT: bucketNo: %d", bucketNo);
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    printDebug(DM_ReplServer, "GSFHT: bucket: %x", stmtBucket);
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        printDebug(DM_ReplServer, "GSFHT: node: %x", node);
        if(stmtId == node->stmtId) {
            printDebug(DM_ReplServer, "GSFHT: stmtId: %d", node->stmtId);
            printDebug(DM_ReplServer, "GSFHT stmt: %x", node->stmt);
            return node->stmt;
        }
    }
    return NULL;
}

DbRetVal writeToConfResFile(void *data, int len, void *stmtBuckets, 
                                              char *dsn)
{
    DbRetVal rv = OK;
    bool isPrmStmt=false;
    char confResFile[1024];
    sprintf(confResFile, "%s", Conf::config.getConflResoFile());
    int fd = open(confResFile, O_WRONLY|O_CREAT| O_APPEND, 0644);
    if (fd < 0) {
        printError(ErrOS, "Could not create conflict Resolution file");
        return ErrOS;
    }
    char buffer[1024];
    char paramStmtString[1024];
    
    char *ptr = (char *) data;
    int datalen = *(int *) ptr; ptr += sizeof(int);
    int txnId = *(int *) ptr; ptr += sizeof(int);
    strcpy(buffer, "SET AUTOCOMMIT OFF;\n");
    int ret = os::write(fd, buffer, strlen(buffer));
    if (ret != strlen(buffer)) {
        printError(ErrOS, "Write error into conf resolution file");
        return ErrOS;
    }
    bool first = true;
    int counter = 0; // if at all the statement is parameterized
    int nop = 0;
    int pos = 0;
    while ((ptr - (char *)data) < len) {
        int stmtId = *(int *)ptr;
        ptr += sizeof(int);
        int bucketNo = getHashBucket(stmtId);
        StmtBucket *buck = (StmtBucket *) stmtBuckets;
        StmtBucket *stmtBucket = &buck[bucketNo];
        StmtNode *node = NULL;
        ListIterator it = stmtBucket->bucketList.getIterator();
        while(it.hasElement()) {
            node = (StmtNode *) it.nextElement();
            if(stmtId == node->stmtId) break;
        }
        printf("DEBUG:node = %x\n", node);
        ExecType type = (ExecType) (*(int *) ptr);
        ptr += sizeof(int);
        if (type == SETPARAM) {
            isPrmStmt = true;
            if (first) { 
                first = false;
                sprintf(paramStmtString, "%s", node->stmtstr);
                char *it = node->stmtstr;
            }
            int parampos = *(int *)ptr;
            ptr += sizeof(int);
            DataType dataType = (DataType) ( *(int *) ptr);
            ptr += sizeof(int);
            int length = *(int *) ptr;
            ptr += sizeof(int);
            void *value = ptr;
            ptr += length;
            char * it = paramStmtString;
            int prntdChars = 0;

            while (*it != '\0') {
                if (*it == '?') { 
                    pos++; 
                    if(pos != parampos) { it++; continue; }
                    else {    
                        *it++ = ' ';
                        strcpy(buffer,it); 
                        switch (dataType) {
                            case typeString: case typeBinary: case typeDate: 
                            case typeTime:   case typeTimeStamp:
                                *it++ = '\'';
                                AllDataType::convertToString(it, value, dataType, length);
                                prntdChars = AllDataType::printVal(value, dataType,length);
                                it += prntdChars;
                                *it++ = '\'';
                                break;
                            default:
                                AllDataType::convertToString(it, value, dataType, length);
                                prntdChars = AllDataType::printVal(value, dataType,length);
                                it += prntdChars;
                           
                        }        
                        sprintf(it, " %s", buffer);
                        //strcpy(buffer, paramStmtString);
                        break;
                    }
                } else { it++; }
            }
        } else {
            if (!isPrmStmt) {
                sprintf(buffer, "%s", node->stmtstr);
                buffer[strlen(buffer)] = '\n';
                ret = os::write(fd, buffer, strlen(node->stmtstr)+1);
                if(ret != strlen(node->stmtstr)+1) {
                    printError(ErrOS, "Write error into conf resolution file");
                    return ErrOS;
                }
            } else {
                strcpy(buffer, paramStmtString);
                isPrmStmt = false;
                first = true;
                pos = 0;
                int strlength = strlen(buffer);
                buffer[strlen(buffer)] = '\n';
                ret = os::write(fd, buffer, strlength+1);
                if(ret != strlength+1) {
                    printError(ErrOS, "Write error into conf resolution file");
                    return ErrOS;
                }
            }
        }
    }
    strcpy(buffer, "COMMIT;\n\n");
    ret = os::write(fd, buffer, strlen(buffer));
    if(ret != strlen(buffer)) {
        printError(ErrOS, "Write error into conf resolution file");
        return ErrOS;
    }
    close(fd);
}
