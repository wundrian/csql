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

typedef struct FailedStmtObject {
    int stmtId;
    DbRetVal eType;
} FailStmt;

typedef struct item ITEM;

struct item
{
    ITEM *next;
    void *data;
};

// please dont touch the following code for queIterator
typedef class queueIterator
{
     ITEM *head;
     ITEM *iter;
     ITEM *processed;
     public:
     queueIterator(ITEM *hd) { head = iter = hd; processed = NULL; }
     inline void *next(ITEM *hd)
     {
         if (head == NULL) { head = iter = hd; }
         if (head != hd) head = hd;
         ITEM *elem = iter;
         if (iter == NULL && processed) {
             if (processed->next != NULL) {
                 processed = processed->next;
                 iter = processed;
                 elem = iter;
             } else { return NULL; }
         }
         processed = elem;
         printDebug(DM_ReplServer, "Processed ITEM: %X", processed);
         iter = iter->next;
         return &elem->data;
     }
} QITER;

class queue
{
    ITEM *head;
    int nItems;
    // array of msg indexes processed, First index for first thread and so on.
    // As and when the msg is read from the queue by each of the threads
    // respcective slot is filled with that index 
    long long *processedMsgIndexArray;
    long long minProcessedMsgIndex;
    long long qIndex;
    long long lastFreedIndex;
    QITER **qIter;
    Mutex qMutex;
    public:
    queue(int asySites)
    {
        nItems = 0; head = NULL; processedMsgIndexArray = NULL;
        qIndex = 0; qIter = NULL;  minProcessedMsgIndex = 0;
        lastFreedIndex = 0;
        qMutex.init();
        int size = sizeof (long long) * asySites;
        processedMsgIndexArray = (long long *) malloc(size);
        memset(processedMsgIndexArray, 0, size);
        qIter = (QITER **) malloc(sizeof (QITER *) * asySites);
        for (int i = 0; i < asySites; i++) qIter[i] = new QITER(head);
    }
    ~queue() {}
    int push(void *log, int len)
    {
        // log includes size of long (msgType) + size of (Msg data);
        // 2nd parameter len is the size of (Msg data) excluding size of long

        // long long for Msg Index
        // int for size of the msg data
        // long for msgType
        // len bytes for msg data
        int logSize = sizeof(long long) + sizeof(int) + sizeof(long) + len;
        ITEM *item = (ITEM *) malloc(sizeof(ITEM) - sizeof(void *)
                                                        + os::align(logSize));
        item->next = NULL;
        char *ptr = (char *) &item->data;
        *(long long *) ptr = ++qIndex; ptr += sizeof (long long);
        *(int*) ptr= len; ptr += sizeof (int);
        int sizeOfMsg = len + sizeof(long);
        memcpy(ptr, log, sizeOfMsg);
        if (head == NULL) { nItems++; head = item; return 0; }
        ITEM *p = head;
        while (p->next != NULL) p = p->next;
        p->next = item;
        nItems++;
        return 0;
    }
    int size() { return nItems; }
    void *readNextMessage(int thrIndex)
    {
       if (head == NULL) return NULL;
       else return qIter[thrIndex]->next(head);
    }
    inline void updateProcessedIndex(int thrInd, int processedIndex)
    {
        processedMsgIndexArray[thrInd] = processedIndex;
    }
    inline long long findMinIndexForFree(int asySites)
    {
        long long minIndex = processedMsgIndexArray[0];
        for (int i=1; i < asySites; i++) {
            if (minIndex > processedMsgIndexArray[i]) {
                minIndex = processedMsgIndexArray[i];
            }
        }
        return minIndex-1;
    }
    void freeMessagesFromQueue(int asySites)
    {
        long long minIndex = findMinIndexForFree(asySites);
        if (minIndex <= lastFreedIndex) return;
        ITEM *elem = head;
        ITEM *freeFrom = head;
        ITEM *freeUptoThis = NULL;
        long long ind = 0;
        while (elem != NULL) {
            ind = * (long long *) &elem->data;
            if (ind == minIndex) {
                freeUptoThis = elem;
                head = elem->next;
                break;
            }
            elem = elem->next;
        }
        ITEM *toFree = elem = freeFrom;
        while (elem != freeUptoThis) {
            toFree = elem;
            elem = elem->next;
            if (toFree) { ::free(toFree); nItems--; }
            printDebug(DM_ReplServer, "FREED %X", toFree);
        }
        if (elem) { ::free(elem); nItems--; }
        printDebug(DM_ReplServer, "FREED %X", elem);
        lastFreedIndex = minIndex;
    }
};

typedef class queue QUE;

class ThreadInputData
{
    public:
    int thrIndex;
    ThreadInputData() { thrIndex = 0; }
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
DbRetVal writeToConfResFile(void *data, int len, void *stmtBuckets, char *dsn);

//Globals
QUE *que = NULL;
int srvStop =0;
int msgKey = 0;
ThreadInputData **thrInput;
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

    if (opt == 10) { printUsage(); return 0; }

    os::signal(SIGINT, sigTermHandler);
    os::signal(SIGTERM, sigTermHandler);

    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    msgKey = os::msgget(Conf::config.getMsgKey(), 0666);
    if (msgKey == -1) {
        printf("Message Queue creation failed\n");
        return 4;
    }
    
    //Only single cache async updation is supported hence hard coded.
    int asyncSites = 1;

    // Create and Initialize repl server queue
    que = new queue(asyncSites);

    pthread_t *thrId =new pthread_t [asyncSites];
    int thrInfoSize = sizeof(ThreadInputData *) * asyncSites;
    thrInput = (ThreadInputData **) malloc(thrInfoSize);
    
    int i=0;
    if(Conf::config.useCache() && Conf::config.getCacheMode()==ASYNC_MODE) {
        thrInput[i] = new ThreadInputData();
        thrInput[i]->thrIndex = i;
        pthread_create(&thrId[i], NULL, &startThread, thrInput[i]);
        i++;
    } 
    pthread_create(&freeThrId, NULL, freeMsgFromQueue, (void *) asyncSites);
    struct timeval timeout;
    int msgSize = Conf::config.getAsyncMsgMax();
    char str[8192];
    
    while (!srvStop) {
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        os::select(0, 0, 0, 0, &timeout);
        printDebug(DM_ReplServer, "waiting for message");
        while(true) {
           // pick messages from message que with key msgKey
           long size = os::msgrcv(msgKey, str, msgSize, 0, 0666|IPC_NOWAIT);
           printDebug(DM_ReplServer, "Received msg size = %d", size);
           if (size == -1 || srvStop) break;
           // push the received msg to the repl server queue
           que->push(str, size);   
        }
    }
    delete[] thrId;
    printf("Replication Server Exiting\n");
    return 0;
}

void *startThread(void *thrInfo)
{
    DbRetVal rv = OK;
    DbRetVal proMsgRetVal = OK;
    void *msg=NULL;
    ThreadInputData *thrInput = (ThreadInputData *)thrInfo;
    List prepareFailList;
    SqlApiImplType flag = CSqlAdapter;
    int thrInd = thrInput->thrIndex;
    printDebug(DM_ReplServer, "SqlAdapter Thread created");
    AbsSqlConnection *conn = SqlFactory::createConnection(flag);
    
    void *stmtBuckets = malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    memset(stmtBuckets, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));
    printDebug(DM_ReplServer, "stmtbuckets: %x", stmtBuckets);
    
    struct timeval timeout, tval;
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
            while (1) {
                if (proMsgRetVal != ErrNoConnection) {
                    msg = NULL;
                    msg = que->readNextMessage(thrInd);
                }
                if (msg != NULL) break;
                tval.tv_sec = 5;
                tval.tv_usec = 1000;
                os::select(0, 0, 0, 0, &tval);
            }
            long long index = *(long long *) msg;
            printDebug(DM_ReplServer, "Received message with index: %lld",
                                                                        index);
            int length = *(int *)((char *)msg+sizeof(long long));             
            char *msgptr = (char *)msg + sizeof(long long) + sizeof(int);
            printDebug(DM_ReplServer, "entering process message");
            proMsgRetVal = processMessage(msgptr, length, conn, stmtBuckets, 
                                                       flag, &prepareFailList);
            if (proMsgRetVal == ErrNoConnection) break;
            printDebug(DM_ReplServer, "Processed message with index: %lld",
                                                                        index);
            //store processed index in the processed index array
            que->updateProcessedIndex(thrInd, index);
            printDebug(DM_ReplServer, "Updated processed index %lld", index);
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

void *freeMsgFromQueue(void *nAsync)
{
    int asySites = (int)nAsync;
    struct timeval tval;
    printDebug(DM_ReplServer, "Waiting for free the q elements");
    while (1) {
        que->freeMessagesFromQueue(asySites);
        tval.tv_sec = 5;
        tval.tv_usec = 0;
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
    SqlStatement::addToHashTable(stmtId, stmt, stmtBuckets, stmtstr);
    printDebug(DM_ReplServer, "returning from prepare");
    return rv;
}; 

DbRetVal handleCommit(void *data, int len, void *conn, void *stmtBuckets, 
                                         List *prepareFailList)
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = (AbsSqlConnection *)conn;
    // get dsn if adapter to write into conflict resolution file
    char *dsstring = NULL;
    SqlOdbcConnection *adCon = (SqlOdbcConnection *) con;
    dsstring = adCon->dsString;
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
        AbsSqlStatement *stmt = SqlStatement::getStmtFromHashTable(stmtId, 
                                                                  stmtBuckets);
        printDebug(DM_ReplServer, "commit: stmtId: %d", stmtId);
        printDebug(DM_ReplServer, "commit: stmtbuckets: %x", stmtBuckets);
        printDebug(DM_ReplServer, "commit: stmt: %x", stmt);
        ExecType type = (ExecType) (*(int *) ptr);
        ptr += sizeof(int);
        if (type == SETPARAM) {
            int parampos = *(int *) ptr;
            ptr += sizeof(int);
            int isNull = *(int *) ptr;
            if (isNull == 0) {
                DataType dataType = (DataType) ( *(int *) ptr);
                ptr += sizeof(int);
                int length = *(int *) ptr;
                ptr += sizeof(int);
                void *value = ptr; 
                ptr += length;
                if (stmt != NULL) 
                    SqlStatement::setParamValues(stmt, parampos, 
                                              dataType, length, (char *)value);
            } else { if (stmt != NULL) stmt->setNull(parampos); }
        } else {
            // start executing and committing for all active connections
            int rows;
            if (stmt != NULL) rv = stmt->execute(rows);
            if (rv != OK) { 
                printError(rv, "Execute failed with return value %d", rv); 
                if (rv == ErrNoConnection) return rv;
                else {
                    // write to conflict resolution file  
                    writeToConfResFile(data, len, stmtBuckets, dsstring);
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
                    writeToConfResFile(data, len, stmtBuckets, dsstring);
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
    AbsSqlStatement *stmt = SqlStatement::getStmtFromHashTable(stmtId, 
                                                                  stmtBuckets);
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
    SqlStatement::removeFromHashTable(stmtId, stmtBuckets);
    printDebug(DM_ReplServer, "Freed the statement from hashTable");
    return OK;
}

DbRetVal writeToConfResFile(void *data, int len, void *stmtBuckets, char *dsn)
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
        int bucketNo = stmtId % STMT_BUCKET_SIZE;
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
