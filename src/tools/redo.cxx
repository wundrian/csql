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
#include <Statement.h>
#include <SqlFactory.h>
#include <SqlStatement.h>

DbRetVal iterateStmtLogs(void *startAddr, int size);
AbsSqlConnection *conn;
void *stmtBuckets = NULL;
bool list = false;
bool interactive=false;
char fileName[MAX_FILE_LEN];
void addToHashTable(int stmtID, AbsSqlStatement* sHdl)
{
    int bucketNo = stmtID % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    StmtNode *node = new StmtNode();
    node->stmtId = stmtID;
    node->stmt = sHdl;
    stmtBucket->bucketList.append(node);
    return; 
}
void removeFromHashTable(int stmtID)
{
    int bucketNo = stmtID % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    StmtNode *node = NULL, *delNode = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtID == node->stmtId) { delNode = node; break; }
    }
    it.reset();
    if (delNode != NULL) {
       stmtBucket->bucketList.remove(delNode);
       delete delNode;
    }
    return;
}
AbsSqlStatement *getStmtFromHashTable(int stmtId)
{
    int bucketNo = stmtId % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    if (stmtBucket == NULL) return NULL;
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtId == node->stmtId) {
            SqlStatement *sqlStmt = (SqlStatement*)node->stmt;
            if (!sqlStmt->isPrepared()) sqlStmt->prepare();
            return node->stmt;
        }
    }
    return NULL;
}

bool isStmtInHashTable(int stmtId)
{
    int bucketNo = stmtId % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    if (stmtBucket == NULL) return false;
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtId == node->stmtId) {
            SqlStatement *sqlStmt = (SqlStatement*)node->stmt;
            if (sqlStmt->isPrepared()) return true;
            else break;
        }
    }
    return false;
}


void freeAllStmtHandles()
{
    if (NULL == stmtBuckets) return;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtNode *node = NULL;
    for (int i=0; i <STMT_BUCKET_SIZE; i++)
    {
        StmtBucket *stmtBucket = &buck[i];
        if (stmtBucket == NULL) continue;
        ListIterator it = stmtBucket->bucketList.getIterator();
        while(it.hasElement()) {
            node = (StmtNode *) it.nextElement();
            node->stmt->free();
            delete node->stmt;
        }
    }
    ::free(stmtBuckets);
}
void setParam(AbsSqlStatement *stmt, int pos, DataType type , int length, void *value)
{
    switch(type)
    {
        case typeInt:
            stmt->setIntParam(pos, *(int*)value);
            break;
        case typeLong:
            stmt->setLongParam(pos, *(long*) value);
            break;
        case typeLongLong:
            stmt->setLongLongParam(pos, *(long long*)value);
            break;
        case typeShort:
            stmt->setShortParam(pos, *(short*)value);
            break;
        case typeByteInt:
            stmt->setByteIntParam(pos, *(ByteInt*)value);
            break;
        case typeDouble:
            stmt->setDoubleParam(pos, *(double*)value);
            break;
        case typeFloat:
            stmt->setFloatParam(pos, *(float*)value);
            break;
        case typeDate:
            stmt->setDateParam(pos, *(Date*)value);
            break;
        case typeTime:
            stmt->setTimeParam(pos, *(Time*)value);
            break;
        case typeTimeStamp:
            stmt->setTimeStampParam(pos, *(TimeStamp*)value);
            break;
        case typeString:
            stmt->setStringParam(pos, (char*)value);
            break;
        case typeBinary:
            stmt->setBinaryParam(pos, value, length);
            break;
        default:
            printf("unknown type\n");
            break;
    }
    return;
}

DbRetVal readAndPopulateStmts()
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    printf("Statement Redo log filename is :%s\n", fName);
    int fd = open(fName, O_RDONLY);
    if (-1 == fd) { return OK; }
    if (fstat(fd, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        close(fd);
        return ErrSysInternal;
    }
    if (NULL != stmtBuckets)
    {
        printError(ErrSysInternal, "stmtBuckets already populated");
        return ErrSysInternal;
    }
    stmtBuckets = malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    memset(stmtBuckets, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));
    if (st.st_size ==0) {
        printError(ErrNote, "No Statement logs found during recovery");
        close(fd);
        return OK;
    }
    void *startAddr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == startAddr) {
        printError(ErrSysInternal, "Unable to mmap stmt log file\n");
        return ErrSysInternal;
    }
    DbRetVal rv = iterateStmtLogs(startAddr, st.st_size);
    munmap((char*)startAddr, st.st_size);
    close(fd);
    return rv;
}
DbRetVal filterAndWriteStmtLogs()
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    int fdRead = open(fName, O_RDONLY);
    if (-1 == fdRead) { return OK; }
    if (fstat(fdRead, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        close(fdRead);
        return ErrSysInternal;
    }
    if (st.st_size ==0) {
        close(fdRead);
        return OK;
    }
    void *startAddr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fdRead, 0);
    if (MAP_FAILED == startAddr) {
        printError(ErrSysInternal, "Unable to mmap stmt log file\n");
        return ErrSysInternal;
    }
    sprintf(fName, "%s/csql.db.stmt1", Conf::config.getDbFile());
    int fd = os::openFileForAppend(fName, O_CREAT|O_TRUNC);
    char *iter = (char*)startAddr;
    char *logStart = NULL, *logEnd = NULL;
    int logType;
    int stmtID;
    int len =0, ret =0;
    DbRetVal rv = OK;
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        logStart = iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            len = *(int*) iter; 
            iter = iter + 2 * sizeof(int);
            stmtID = *(int*)iter;
            iter = logStart+ len;
            ret =0;
            if (isStmtInHashTable(stmtID))
                ret = os::write(fd, logStart, len);
            if (-1 == ret) {
                printError(ErrSysInternal, "Unable to write statement logs");
            }
        }
        else if(logType == -3) { //free
            iter = logStart + 4 *sizeof(int);
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }
    os::closeFile(fd);
    munmap((char*)startAddr, st.st_size);
    close(fdRead);
    char cmd[MAX_FILE_LEN *2];
    sprintf(cmd, "mv %s/csql.db.stmt1 %s/csql.db.stmt", 
                  Conf::config.getDbFile(), Conf::config.getDbFile());
    ret = system(cmd);
    return rv;
}
DbRetVal iterateStmtLogs(void *startAddr, int size)
{
    char *iter = (char*)startAddr;
    void *value = NULL;
    int logType, eType;
    int stmtID;
    int txnID;
    int len, ret, retVal =0;
    int loglen;
    char stmtString[SQL_STMT_LEN];
    DbRetVal rv = OK;
    while(true) {
        if (iter - (char*)startAddr >= size) break;
        logType = *(int*)iter;
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            iter = iter + sizeof(int);
            len = *(int*)iter;
            iter = iter + sizeof(int);
            strncpy(stmtString, iter, len);
            iter = iter + len;
            if (list) {
                printf("PREPARE: SID:%d %s\n", stmtID, stmtString);
                continue;
            }
            if (interactive) printf("STMTLOG PREPARE SID:%d %s\n", stmtID, stmtString);
            AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
            stmt->setConnection(conn);
            SqlStatement *sqlStmt = (SqlStatement*)stmt;
            sqlStmt->setStmtString(stmtString);
            addToHashTable(stmtID, stmt);
        }
        else if(logType == -3) { //free
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            iter = iter + sizeof(int);
            if (list) {
                printf("FREE: SID:%d TID:%d \n", stmtID, txnID);
                continue;
            }
        }else{
            printError(ErrSysInternal, "Stmt Redo log file corrupted: logType:%d", logType);
            rv = ErrSysInternal;
            break;
        }
    }
    return rv;
}

int main(int argc, char **argv)
{
    struct stat st;
    strcpy(fileName, "");
    int c = 0, opt=0; 
    while ((c = getopt(argc, argv, "f:ail?")) != EOF) {
        switch (c) {
            case '?' : { opt = 1; break; } //print help 
            case 'a' : { opt = 2; break; } 
            case 'i' : { interactive = true; break; }
            case 'l' : { list = true; break; }
            case 'f' : {strcpy(fileName , argv[optind - 1]); break;}
            default: printf("Wrong args\n"); exit(1);

        }
    }//while options
    if (2 !=opt) {
       printf("This is an internal csql command with i and f <filename> options.");
       exit(1);
    }
    char *verbose =  os::getenv("CSQL_INTERACTIVE");
    if (verbose !=NULL && strcmp(verbose, "true") == 0)
    {
        printf("VERBOSE ON %s\n", verbose);
        interactive=true;
    }

    
    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    if (strcmp(fileName, "") ==0) {
        sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    }
    int fd = open(fileName, O_RDONLY);
    if (-1 == fd) { return OK; }
    if (fstat(fd, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve undo log file size");
        close(fd);
        return 1;
    }
    if (st.st_size ==0) {
        printError(ErrNote, "No Redo logs found during recovery");
        readAndPopulateStmts();
        close(fd);
        return 0;
    }
    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(I_USER, I_PASS);
    SqlConnection *sCon = (SqlConnection*) conn;
    if(!list) rv = sCon->getExclusiveLock();
    //during connection close, this exclusive lock will be automatically released
    if (rv != OK) {
        close(fd);
        conn->disconnect();
        delete conn;
        return 1;
    }
    void *startAddr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == startAddr) {
        printf("Unable to read undo log file:mmap failed.\n");
        conn->disconnect();
        delete conn;
        return 2;
    }
    rv = readAndPopulateStmts();
    if (OK != rv)
    {
        printf("Unable to read stmt log file\n");
        conn->disconnect();
        delete conn;
        return 2;
    }

    printf("Redo log filename is :%s\n", fileName);
    char *iter = (char*)startAddr;
    void *value = NULL;
    int logType, eType;
    int stmtID;
    int txnID;
    int len, ret, retVal =0;
    int loglen;
    char stmtString[SQL_STMT_LEN];
    //printf("size of file %d\n", st.st_size);
    while(true) {
        //printf("OFFSET HERE %d\n", iter - (char*)startAddr);
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter; 
        if (logType == -1) { //prepare
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            iter = iter + sizeof(int);
            len = *(int*)iter;
            iter = iter + sizeof(int);
            strncpy(stmtString, iter, len);
            iter = iter + len;
            if (list) {
                printf("PREPARE: SID:%d %s\n", stmtID, stmtString);
                continue;
            }
            AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
            stmt->setConnection(conn);
            if (interactive) printf("PREPARE %d : %s\n", stmtID, stmtString);
            rv = stmt->prepare(stmtString);
            if (rv != OK) { 
                printError(ErrSysInternal, "unable to prepare stmt:%s", stmtString); 
                retVal=1;
                break;
            }
            SqlStatement *sqlStmt = (SqlStatement*)stmt; 
            sqlStmt->setLoading(true);
            addToHashTable(stmtID, stmt); 
        }    
        else if(logType == -2) { //commit
            conn->beginTrans();
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            char *curPtr = iter;
            while(true) {
                //printf("Iter length %d\n", iter - curPtr);
                if (iter - (char*)startAddr >= st.st_size) {
                    //file end reached
                    //printf("Redo log file end\n");
                    retVal=0;
                    break;
                }
                stmtID = *(int*)iter;
                //printf("stmtid %d\n", stmtID);
                if (interactive) printf("EXEC %d :\n", stmtID);
                iter = iter + sizeof(int);
                eType = *(int*)iter;
                //printf("eType is %d\n", eType);
                AbsSqlStatement *stmt = NULL;
                if (!list) {
                  stmt = getStmtFromHashTable(stmtID);
                  if (NULL == stmt) {
                    printError(ErrSysInternal, "Unable to find in stmt hashtable");
                    retVal=2;
                    break;
                  }
                }
                if (0 == eType) { //execute type
                    iter = iter + sizeof(int);
                    if (list) {
                        printf("EXEC SID:%d TID:%d\n", stmtID, txnID);
                        if (*(int*)iter <0) break;
                        continue;
                    }
                    if (stmt) { 
                        rv = stmt->execute(ret);
                        if (rv != OK) { 
                            printError(ErrSysInternal, "unable to execute"); 
                            retVal=2;
                            break;
                        }
                    } else {
                        printError(ErrSysInternal, "statement not found for %d\n",stmtID);
                    }
                    if (*(int*)iter <0) break;
                } else if ( 1 == eType) { //set type
                    iter=iter+sizeof(int);
                    int pos = *(int*) iter;
                    iter=iter+sizeof(int);
                    DataType type = (DataType)(*(int*)iter);
                    iter=iter+sizeof(int);
                    int len = *(int*) iter;
                    iter=iter+sizeof(int);
                    value = iter;
                    iter=iter+len;
                    if (list) {
                        printf("SET SID:%d POS:%d TYPE:%d LEN:%d Value:", stmtID, pos, type, len);
                        AllDataType::printVal(value, type, len);
                        printf("\n");
                        if (*(int*)iter <0) break;
                        continue;
                    }
                    setParam(stmt, pos, type, len, value);
                    if (*(int*)iter <0) break;
                }
            }
            conn->commit();
        } 
        else if(logType == -3) { //free
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            iter = iter + sizeof(int);
            if (list)  {
               printf("FREE SID:%d \n", stmtID);
               continue;
            }
            if (interactive) printf("FREE %d:\n", stmtID);
            AbsSqlStatement *stmt = getStmtFromHashTable(stmtID);
            if (stmt) {
                stmt->free();
                delete stmt;
                removeFromHashTable(stmtID);
            } else { printError(ErrSysInternal, "statement not found for %d\n",stmtID);}
        }    
        else if(logType == -4) { //prepare and execute
            iter = iter + sizeof(int);
            txnID = *(int*) iter; iter += sizeof(int);
            loglen = *(int*) iter; iter += sizeof(int);
            stmtID = *(int*)iter;
            iter = iter + sizeof(int);
            len = *(int*)iter;
            iter = iter + sizeof(int);
            strncpy(stmtString, iter, len);
            stmtString[len+1] ='\0';
            iter = iter + len;
            if (list)  {
               printf("EXECDIRECT SID:%d TID:%d STMT:%s\n", stmtID, txnID, stmtString);
               continue;
            }
            AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
            if ( NULL == stmt) {
                printError(ErrSysInternal, "unable to prepare:%s", stmtString); 
                retVal=3;
                break;
            }
            stmt->setConnection(conn);
            if (interactive) printf("EXECDIRECT %d : %s\n", stmtID, stmtString);
            rv = stmt->prepare(stmtString);
            if (rv != OK) {
                printError(ErrSysInternal, "unable to prepare:%s", stmtString); 
                stmt->free();
                delete stmt;
                retVal=4;
                break;
            }
            rv = stmt->execute(ret);
            if (rv != OK) {
                if (strlen(stmtString) > 6 && 
                    ( (strncasecmp(stmtString,"CREATE", 6) == 0) ||
                      (strncasecmp(stmtString,"DROP", 4) == 0)) ) {
            //        conn->disconnect();
              //      return OK;
                    continue;
                }
                printError(ErrSysInternal, "unable to execute %s", stmtString); 
                stmt->free();
                retVal=5;
                break;
            }
            stmt->free();
            delete stmt;
        }else{
            printError(ErrSysInternal, "Redo log file corrupted: logType:%d", logType);
            retVal=6;
            break;
        }
    }
    munmap((char*)startAddr, st.st_size);
    close(fd);
    if (!list) {
        filterAndWriteStmtLogs();
        freeAllStmtHandles();
    }
    conn->disconnect();
    delete conn;
    return retVal;
}
