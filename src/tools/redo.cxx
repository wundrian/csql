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

AbsSqlConnection *conn;
void *stmtBuckets = NULL;
bool list = false;
bool interactive=false;
char fileName[MAX_FILE_LEN];

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

    conn = SqlFactory::createConnection(CSqlDirect);
    DbRetVal rv = conn->connect(I_USER, I_PASS);
    if (rv != OK) {
        printError(ErrNoConnection, "REDO: could not connect to DB.");
        delete conn;
        return 2;
    }
 
    if (strcmp(fileName, "") ==0) {
        sprintf(fileName, "%s/csql.db.cur", Conf::config.getDbFile());
    }
    int fd = open(fileName, O_RDONLY);
    if (-1 == fd) { conn->disconnect(); delete conn; return OK; }
    if (fstat(fd, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve undo log file size");
        close(fd);
        conn->disconnect();
        delete conn;
        return 3;
    }
    if (st.st_size ==0) {
        printError(ErrNote, "No Redo logs found during recovery");
        SqlStatement::readAndPopulateStmts(conn, stmtBuckets, list, interactive);
        close(fd);
        conn->disconnect();
        delete conn;
        return 0;
    }
    SqlConnection *sCon = (SqlConnection*) conn;
    if(!list) rv = sCon->getExclusiveLock();
    //during connection close, this exclusive lock will be automatically released
    if (rv != OK) {
        close(fd);
        conn->disconnect();
        delete conn;
        return 4;
    }
    void *startAddr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == startAddr) {
        printf("Unable to read undo log file:mmap failed.\n");
        conn->disconnect();
        delete conn;
        return 5;
    }
    rv = SqlStatement::readAndPopulateStmts(conn, stmtBuckets, list, interactive);
    if (OK != rv)
    {
        printf("Unable to read stmt log file\n");
        conn->disconnect();
        delete conn;
        return 6;
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
            SqlStatement::addToHashTable(stmtID, stmt,stmtBuckets, stmtString); 
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
                  stmt = SqlStatement::getStmtFromHashTable(stmtID,stmtBuckets);
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
                    int isNull = *(int *) iter;
                    iter=iter+sizeof(int);
                    if (isNull == 0) {
                        DataType type = (DataType)(*(int*)iter);
                        iter=iter+sizeof(int);
                        int len = *(int*) iter;
                        iter=iter+sizeof(int);
                        value = iter;
                        iter=iter+len;
                        if (list) {
                            printf("SET SID:%d POS:%d ISNULL:FALSE TYPE:%d LEN:%d Value:", stmtID, pos, type, len);
                            AllDataType::printVal(value, type, len);
                            printf("\n");
                            if (*(int*)iter <0) break;
                            continue;
                        }
                        SqlStatement::setParamValues(stmt, pos, type, len, value);
                    } else {
                        if (list) {
                            printf("SET SID:%d POS:%d ISNULL:TRUE\n", stmtID, pos);
                            continue;
                        }
                        stmt->setNull(pos);
                    }
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
            AbsSqlStatement *stmt = SqlStatement::getStmtFromHashTable(stmtID,
                                                                  stmtBuckets);
            if (stmt) {
                stmt->free();
                delete stmt;
                SqlStatement::removeFromHashTable(stmtID,stmtBuckets);
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
                      (strncasecmp(stmtString,"DROP", 4) == 0)   ||
                      (strncasecmp(stmtString,"RENAME", 6) == 0) ||
                      (strncasecmp(stmtString,"ALTER", 5) == 0)) ) {

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
        SqlStatement::filterAndWriteStmtLogs(stmtBuckets);
        SqlStatement::freeAllStmtHandles(stmtBuckets);
    }
    conn->disconnect();
    delete conn;
    return retVal;
}
