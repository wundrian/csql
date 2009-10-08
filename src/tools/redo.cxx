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
#define SQL_STMT_LEN 1024
#define DEBUG 1

AbsSqlConnection *conn;
void *stmtBuckets;
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
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtID == node->stmtId) break;
    }
    it.reset();
    stmtBucket->bucketList.remove(node);
    return;
}
AbsSqlStatement *getStmtFromHashTable(int stmtId)
{
    int bucketNo = stmtId % STMT_BUCKET_SIZE;
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    StmtNode *node = NULL;
    ListIterator it = stmtBucket->bucketList.getIterator();
    while(it.hasElement()) {
        node = (StmtNode *) it.nextElement();
        if(stmtId == node->stmtId) {
            return node->stmt;
        }
    }
    return NULL;
}
void freeAllStmtHandles()
{
    //TODO
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

int main(int argc, char **argv)
{
    struct stat st;
    char fileName[1024];
    int c = 0, opt=0; 
    bool interactive=0;
    while ((c = getopt(argc, argv, "ai?")) != EOF) {
        switch (c) {
            case '?' : { opt = 1; break; } //print help 
            case 'a' : { opt = 2; break; } 
            case 'i' : { interactive = 1; break; }
            default: printf("Wrong args\n"); exit(1);

        }
    }//while options
    if (2 !=opt) {
       printf("This is an internal csql command.");
       exit(1);
    }
    Conf::config.readAllValues(os::getenv("CSQL_CONFIG_FILE"));
    sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    printf("Redo log filename is :%s\n", fileName);
    int fd = open(fileName, O_RDONLY);
    if (-1 == fd) { return OK; }
    if (fstat(fd, &st) == -1) {
        printf("Unable to retrieve undo log file size\n");
        close(fd);
        return ErrUnknown;
    }
    if (st.st_size ==0) {
        printf("Nothing in redo log file\n");
        close(fd);
        return 0;
    }
    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(I_USER, I_PASS);
    SqlConnection *sCon = (SqlConnection*) conn;
    rv = sCon->getExclusiveLock();
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
    stmtBuckets = malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    memset(stmtBuckets, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));

    char *iter = (char*)startAddr;
    void *value;
    int logType, eType;
    int stmtID;
    int txnID;
    int len, ret;
    int loglen;
    char stmtString[1024];
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
            //printf("PREPARE:%d %d %s\n", stmtID, len, stmtString);
            AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
            stmt->setConnection(conn);
            if (interactive) printf("PREPARE %d : %s\n", stmtID, stmtString);
            rv = stmt->prepare(stmtString);
            if (rv != OK) { 
                printf("unable to prepare\n"); 
                conn->disconnect();
                return ErrSysFatal; 
            }
            stmt->prepare(stmtString);
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
                    conn->commit();
                    freeAllStmtHandles();
                    conn->disconnect();
                    munmap((char*)startAddr, st.st_size);
                    close(fd);
                    delete conn;
                    return 0;
                }
                stmtID = *(int*)iter;
                //printf("stmtid %d\n", stmtID);
                if (interactive) printf("EXEC %d :\n", stmtID);
                iter = iter + sizeof(int);
                eType = *(int*)iter;
                //printf("eType is %d\n", eType);
                AbsSqlStatement *stmt = getStmtFromHashTable(stmtID);
                if (0 == eType) { //execute type
                    iter = iter + sizeof(int);
                    //printf("EXEC: %d\n", stmtID);
                    if (stmt) { 
                        rv = stmt->execute(ret);
                        if (rv != OK) { 
                            //printf("execute failed\n"); 
                            conn->disconnect();
                            return ErrSysFatal; 
                        }
                    } else {
                        printf("statement not found for %d\n",stmtID);
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
                    //AllDataType::printVal(value, type, len);
                    iter=iter+len;
                    //printf("SET: %d %d %d %d\n", stmtID, pos, type, len);
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
            if (interactive) printf("FREE %d:\n", stmtID);
            AbsSqlStatement *stmt = getStmtFromHashTable(stmtID);
            if (stmt) {
                stmt->free();
                removeFromHashTable(stmtID);
            } else { printf("statement not found for %d\n",stmtID);}
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
            //printf("CREATE:%d %d %s\n", stmtID, len, stmtString);
            AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
            if ( NULL == stmt) {
                printf("unable to prepare\n"); 
                conn->disconnect();
                return ErrSysFatal;
            }
            stmt->setConnection(conn);
            if (interactive) printf("EXECDIRECT %d : %s\n", stmtID, stmtString);
            rv = stmt->prepare(stmtString);
            if (rv != OK) {
                printf("unable to prepare\n"); 
                conn->disconnect();
                return ErrSysFatal;
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
                printf("unable to execute\n"); 
                conn->disconnect();
                return ErrSysFatal;
            }
            stmt->free();
        }
    }
    munmap((char*)startAddr, st.st_size);
    close(fd);
    freeAllStmtHandles();
    conn->disconnect();
    delete conn;
    return 0;
}
