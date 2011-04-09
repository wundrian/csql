/**************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <os.h>
#include <Recover.h>

void Recovery::addToHashTable(int stmtID, AbsSqlStatement* sHdl,
                             char *stmtstr)
{
    int bucketNo = stmtID % STMT_BUCKET_SIZE;
    printDebug(DM_Recovery, "Inside addToHashTable %x", stmtBuckets);
    StmtBucket *buck = (StmtBucket *) stmtBuckets;
    StmtBucket *stmtBucket = &buck[bucketNo];
    StmtNode *node = new StmtNode();
    node->stmtId = stmtID;
    node->stmt = sHdl;
    strcpy(node->stmtstr, stmtstr);
    stmtBucket->bucketList.append(node);
    return;
}

void Recovery::removeFromHashTable(int stmtID)
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

AbsSqlStatement* Recovery::getStmtFromHashTable(int stmtId)
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
            if (!sqlStmt->isPrepared()) sqlStmt->prepare(node->stmtstr);
            return node->stmt;
        }
    }
    return NULL;
}

bool Recovery::isStmtInHashTable(int stmtId)
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

void Recovery::freeAllStmtHandles()
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
    stmtBuckets = NULL;
}

DbRetVal Recovery::filterAndWriteStmtLogs()
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    file_desc fdRead = os::openFile(fName, fileOpenReadOnly,0);
    if ((file_desc)-1 == fdRead) { return OK; }
    if (::stat(fName, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        os::closeFile(fdRead);
        return ErrSysInternal;
    }
    if (st.st_size ==0) {
        os::closeFile(fdRead);
        return OK;
    }
    void *startAddr = os::mmap(NULL, st.st_size, mapProtRead, mapPrivate, fdRead, 0);
    if ((void*)MAP_FAILED == startAddr) {
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
    os::close(fd);
    os::munmap((char*)startAddr, st.st_size);
    os::closeFile(fdRead);
    char cmd[MAX_FILE_LEN *2];
    sprintf(cmd, "mv %s/csql.db.stmt1 %s/csql.db.stmt",
                  Conf::config.getDbFile(), Conf::config.getDbFile());
    ret = ::system(cmd);
    return rv;
}

DbRetVal Recovery::readAndPopulateStmts(AbsSqlConnection *conn, bool list, bool interactive)
{
    struct stat st;
    char fName[MAX_FILE_LEN];
    sprintf(fName, "%s/csql.db.stmt", Conf::config.getDbFile());
    printDebug(DM_Recovery,"Statement Redo log filename is :%s\n", fName);
    file_desc fd = os::openFile(fName, fileOpenReadOnly, 0);
    if ((file_desc)-1 == fd) { 
        printDebug(DM_Recovery, "No redo log file found");
        return OK; 
    }
    if (::stat(fName, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve stmt log file size");
        os::closeFile(fd);
        return ErrSysInternal;
    }
    if (NULL != stmtBuckets)
    {
        printError(ErrSysInternal, "stmtBuckets already populated");
        os::closeFile(fd);
        return ErrSysInternal;
    }
    stmtBuckets = (void*) ::malloc (STMT_BUCKET_SIZE * sizeof(StmtBucket));
    printDebug(DM_Recovery, "stmtBuckets allocated %x", stmtBuckets);
    memset(stmtBuckets, 0, STMT_BUCKET_SIZE * sizeof(StmtBucket));
    if (st.st_size ==0) {
        printError(ErrNote, "No Statement logs found during recovery");
        os::closeFile(fd);
        return OK;
    }
    void *startAddr = os::mmap(NULL, st.st_size, mapProtRead, mapPrivate, fd, 0);
    if ((void*)MAP_FAILED == startAddr) {
        printError(ErrSysInternal, "Unable to mmap stmt log file\n");
        ::free(stmtBuckets);
        stmtBuckets = NULL;
        os::closeFile(fd);
        return ErrSysInternal;
    }
    DbRetVal rv = iterateStmtLogs(conn, startAddr, st.st_size, list, interactive);
    os::munmap((char*)startAddr, st.st_size);
    os::closeFile(fd);
    return rv;
}

DbRetVal Recovery::iterateStmtLogs(AbsSqlConnection *conn, void *startAddr, int size, bool list, bool interactive)
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
            AbsSqlStatement *csqlStmt = SqlFactory::createStatement(CSqlDirect);
            csqlStmt->setConnection(conn);
            SqlStatement *sqlStmt = (SqlStatement*)csqlStmt;
            sqlStmt->setStmtString(stmtString);
            addToHashTable(stmtID, csqlStmt, stmtString);
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

#if (defined MMDB && defined EMBED)

DbRetVal Recovery::recoverCsqlDB()
{
    DbRetVal rv = OK;
    char dbRedoFileName[MAX_FILE_LEN];
    char dbChkptSchema[MAX_FILE_LEN];
    char dbChkptMap[MAX_FILE_LEN];
    char dbChkptData[MAX_FILE_LEN];
    char dbBackupFile[MAX_FILE_LEN];
    char cmd[IDENTIFIER_LENGTH];
    //check for check point file if present recover 
    sprintf(dbChkptSchema, "%s/db.chkpt.schema1", Conf::config.getDbFile());
    if (FILE *file = fopen(dbChkptSchema, "r")) {
        fclose(file);
        sprintf(cmd, "cp -f %s %s/db.chkpt.schema", dbChkptSchema, 
                                                     Conf::config.getDbFile());
        int ret = system(cmd);
        if (ret != 0) return ErrOS;
    }
    sprintf(dbChkptMap, "%s/db.chkpt.map1", Conf::config.getDbFile());
    if (FILE *file = fopen(dbChkptMap, "r")) {
        fclose(file);
        sprintf(cmd, "cp -f %s %s/db.chkpt.map", dbChkptMap, 
                                                     Conf::config.getDbFile());
        int ret = system(cmd);
        if (ret != 0) return ErrOS;
    }
    int chkptID= Database::getCheckpointID();
    sprintf(dbChkptData, "%s/db.chkpt.data%d", Conf::config.getDbFile(),
                                                                      chkptID);
    sprintf(dbBackupFile, "%s/db.chkpt.data1", Conf::config.getDbFile());
    FILE *fl = NULL;
    if (!Conf::config.useMmap() && (fl = fopen(dbBackupFile, "r"))) {
        fclose(fl);
        sprintf(cmd, "cp %s/db.chkpt.data1 %s", Conf::config.getDbFile(), 
                                                                  dbChkptData);
        int ret = system(cmd);
        if (ret != 0) return ErrOS;
    }
    if (FILE *file = fopen(dbChkptData, "r")) {
        fclose(file);
        rv = recoverSystemAndUserDB();
        if (rv != OK) return rv;
    }

    //check for redo log file if present apply redo logs
    sprintf(dbRedoFileName, "%s/csql.db.cur", Conf::config.getDbFile());
    if (FILE *file = fopen(dbRedoFileName, "r"))
    {
        fclose(file);
        rv = (DbRetVal) applyRedoLogs(dbRedoFileName);
        if (rv != OK) return rv;
        DatabaseManager *dbMgr = getConnObject().getDatabaseManager();
        rv = dbMgr->checkPoint();
        if (rv != OK)
        {
            printError(ErrSysInternal, "checkpoint failed after redo log apply");
            return ErrOS;
        }
    }
    return OK;   
}

DbRetVal Recovery::recoverSystemAndUserDB()
{
    DbRetVal rv = OK;
    char schFile[1024];
    sprintf(schFile, "%s/db.chkpt.schema", Conf::config.getDbFile());
    if (FILE *file = fopen(schFile, "r")) {
        rv = applySchemaFile(file);
        if (rv != OK) { fclose(file); return rv; }
    }
    DatabaseManager *dbMgr = getConnObject().getDatabaseManager();
    rv = dbMgr->recover();
    return rv; 
}

DbRetVal Recovery::applySchemaFile(FILE *fp)
{
    char buf[8192];
    char eof;
    DbRetVal rv = OK;
    SqlStatement *stmt = new SqlStatement();
    while ((eof = getQueryFromSchemaFile(fp,buf)) != EOF) {
        stmt->setConnection(this);
        rv = stmt->prepare(buf);
        if (rv != OK) { delete stmt; return rv; }
        int rows = 0;
        stmt->execute(rows);
        if (rv != OK) { stmt->free(); delete stmt; return rv; }
    } 
    delete stmt;
    return OK; 
}

char Recovery::getQueryFromSchemaFile(FILE *fp, char *buf)
{
    char c, *bufBegin=buf;
    int charCnt=0;
    while( (c=(char ) fgetc(fp)) != EOF && c != ';')
    {
        *buf++ = c; charCnt++;
    if( charCnt == SQL_STMT_LEN ) {
            printf("SQL Statement length is greater than %d. "
        "Ignoring the statement.\n", SQL_STMT_LEN );
            *bufBegin++ =';';
            *bufBegin ='\0';
        return 0;
    }
    }
    *buf++ = ';';
    *buf = '\0';
    return c;
}
#endif
int Recovery::applyRedoLogs(char *redoFile, AbsSqlConnection *conn, bool list, bool interactive )
{
    struct stat st;
    DbRetVal rv = OK;
    file_desc fd = os::openFile(redoFile, fileOpenReadOnly, 0);
    if ((file_desc)-1 == fd) { return OK; }
    if (fstat(fd, &st) == -1) {
        printError(ErrSysInternal, "Unable to retrieve undo log file size");
        os::closeFile(fd);
        return 1;
    }
    if (st.st_size ==0) {
        printError(ErrNote, "No Redo logs found during recovery");
        readAndPopulateStmts(conn, list, interactive); 
        os::closeFile(fd);
        return 0;
    }
    void *startAddr = os::mmap(NULL, st.st_size, mapProtRead, mapPrivate, fd, 0);
    if (MAP_FAILED == startAddr) {
        printf("Unable to read undo log file:mmap failed.\n");
        return 3;
    }

    rv = readAndPopulateStmts(conn, list, interactive);
    if (OK != rv)
    {
        printf("Unable to read stmt log file\n");
        return 4;
    }

    iter = (char*)startAddr;
    void *value = NULL;
    int logType, eType;
    int stmtID;
    int txnID;
    int len, ret, retVal =0;
    int loglen;
    char stmtString[SQL_STMT_LEN];
    printDebug(DM_Recovery,"Redo log filename is :%s\n", redoFile);
    while(true) {
        if (iter - (char*)startAddr >= st.st_size) break;
        logType = *(int*)iter;
        if (logType == -1) { //prepare
            rv = handlePrepare(conn, list, interactive);
            if (rv != OK) {
                printError(ErrSysInternal, "unable to handle prepare stmt");
                retVal=1;
                break;
            }
        }
        else if(logType == -2) { //commit
            rv = handleCommit(conn, startAddr, st.st_size, list, interactive);
            if (ErrEndReached == rv)
            {
                printDebug(DM_Recovery, "During Commit processing, end redo log reached");
                retVal=0;
                break;
            }else if (OK != rv) {
                printError(ErrSysInternal, "unable to handle prepare stmt");
                retVal=1;
                break;
            }
        }
        else if(logType == -3) { //free
            handleFree(list, interactive);
        }
        else if(logType == -4) { //prepare and execute
            handlePrepareAndExecute(conn, list, interactive);
        } else {
            printError(ErrSysInternal, "Redo log file corrupted: logType:%d", logType);
            retVal=6;
            break;
        }
    }
    printDebug(DM_Recovery, "Before munmap");
    os::munmap((char*)startAddr, st.st_size);
    os::closeFile(fd);
    if (!list) {
        //when redo log list option is specified do not write statement logs 
        //it will block debugging and change the state at which problem
        //occurred
        printDebug(DM_Recovery, "Before filter and writestmt logs");
        filterAndWriteStmtLogs();
        printDebug(DM_Recovery, "Before freeallstmthandles");
        freeAllStmtHandles();
    }
    return retVal;
}
DbRetVal Recovery::handlePrepare( AbsSqlConnection *conn, bool list, bool interactive)
{
    char stmtString[SQL_STMT_LEN];
    iter = iter + sizeof(int);
    int txnID = *(int*) iter; 
    iter += sizeof(int);
    int loglen = *(int*) iter; 
    iter += sizeof(int);
    int stmtID = *(int*)iter;
    iter = iter + sizeof(int);
    int len = *(int*)iter;
    iter = iter + sizeof(int);
    strncpy(stmtString, iter, len);
    iter = iter + len;
    printDebug(DM_Recovery,"PREPARE: SID:%d %s\n", stmtID, stmtString);
    if (list) {
        printf("PREPARE: SID:%d %s\n", stmtID, stmtString);
        return OK;
    }
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
    stmt->setConnection(conn);
    if (interactive) printf("PREPARE %d : %s\n", stmtID, stmtString);
    DbRetVal rv = stmt->prepare(stmtString);
    if (rv != OK) {
        printError(ErrSysInternal, "unable to prepare stmt:%s", stmtString);
        return ErrSysInternal;
    }
    SqlStatement *sqlStmt = (SqlStatement*)stmt;
    sqlStmt->setLoading(true);
    addToHashTable(stmtID, stmt, stmtString);
    printDebug(DM_Recovery,"Added to hashtable SID:%d ", stmtID);
    return OK;
}
DbRetVal Recovery::handleCommit(AbsSqlConnection *conn, void *startAddr, long size,  bool list, bool interactive)
{
    conn->beginTrans();
    iter = iter + sizeof(int);
    int txnID = *(int*) iter; iter += sizeof(int);
    int loglen = *(int*) iter; iter += sizeof(int);
    char *curPtr = iter;
    DbRetVal rv = OK;
    int ret =0;
    void *value = NULL;
    while(true) {
        printDebug(DM_Recovery, "Iter length %d\n", iter - curPtr);
        if (iter - (char*)startAddr >= size) {
            //file end reached
            printDebug(DM_Recovery, "Redo log file end\n");
            return ErrEndReached;
        }
        int stmtID = *(int*)iter;
        printDebug(DM_Recovery, "stmtid %d\n", stmtID);
        if (interactive) printf("EXEC %d :\n", stmtID);
        iter = iter + sizeof(int);
        int eType = *(int*)iter;
        printDebug(DM_Recovery,"eType is %d\n", eType);
        AbsSqlStatement *stmt = NULL;
        if (!list) {
            stmt = getStmtFromHashTable(stmtID);
            if (NULL == stmt) {
                printError(ErrSysInternal, "Unable to find in stmt hashtable");
                return ErrSysInternal;
            }
        }
        if (0 == eType) { //execute type
            iter = iter + sizeof(int);
            printDebug(DM_Recovery, "EXEC SID:%d TID:%d\n", stmtID, txnID);
            if (list) {
                printf("EXEC SID:%d TID:%d\n", stmtID, txnID);
                if (*(int*)iter <0) break;
                continue;
            }
            if (stmt) {
                rv = stmt->execute(ret);
                if (rv != OK) {
                    printError(ErrSysInternal, "unable to execute");
                    return ErrSysInternal;
                }
            } else {
                printError(ErrSysInternal, "statement not found for %d\n",stmtID);
            }
            printDebug(DM_Recovery, "iter:%x value:%d", iter, *(int*)iter);
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
                printDebug(DM_Recovery, "SET SID:%d POS:%d ISNULL:FALSE TYPE:%d LEN:%d Value:", stmtID, pos, type, len);
                if (list) {
                    printf("SET SID:%d POS:%d ISNULL:FALSE TYPE:%d LEN:%d Value:", stmtID, pos, type, len);
                    AllDataType::printVal(value, type, len);
                    printf("\n");
                    if (*(int*)iter <0) break;
                    continue;
                }
                SqlStatement::setParamValues(stmt, pos, type, len, value);
            } else {
                printDebug(DM_Recovery, "SET SID:%d POS:%d ISNULL:TRUE\n", stmtID, pos);
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
    return OK;
}
DbRetVal Recovery::handleFree(bool list, bool interactive)
{
    iter = iter + sizeof(int);
    int txnID = *(int*) iter; iter += sizeof(int);
    int loglen = *(int*) iter; iter += sizeof(int);
    int stmtID = *(int*)iter;
    iter = iter + sizeof(int);
    printDebug(DM_Recovery, "FREE SID:%d \n", stmtID);
    if (list)  {
        printf("FREE SID:%d \n", stmtID);
        return OK;
    }
    if (interactive) printf("FREE %d:\n", stmtID);
    AbsSqlStatement *stmt = getStmtFromHashTable(stmtID);
    if (stmt) {
        stmt->free();
        delete stmt;
        removeFromHashTable(stmtID);
    } else { 
        printError(ErrSysInternal, "statement not found for %d\n",stmtID);
    }
    return OK;
}
DbRetVal Recovery::handlePrepareAndExecute(AbsSqlConnection *conn, bool list, bool interactive)
{
    int ret = 0;
    DbRetVal rv = OK;
    char stmtString[SQL_STMT_LEN];
    iter = iter + sizeof(int);
    int txnID = *(int*) iter; iter += sizeof(int);
    int loglen = *(int*) iter; iter += sizeof(int);
    int stmtID = *(int*)iter;
    iter = iter + sizeof(int);
    int len = *(int*)iter;
    iter = iter + sizeof(int);
    strncpy(stmtString, iter, len);
    iter = iter + len;
    printDebug(DM_Recovery, "EXECDIRECT SID:%d TID:%d STMT:%s\n", stmtID, txnID, stmtString);
    if (list)  {
        printf("EXECDIRECT SID:%d TID:%d STMT:%s\n", stmtID, txnID, stmtString);
        return OK;
    }
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlDirect);
    if ( NULL == stmt) {
        printError(ErrSysInternal, "unable to prepare:%s", stmtString);
        return ErrSysInternal;
    }
    stmt->setConnection(conn);
    if (interactive) printf("EXECDIRECT %d : %s\n", stmtID, stmtString);
    rv = stmt->prepare(stmtString);
    if (rv != OK) {
        printError(ErrSysInternal, "unable to prepare:%s", stmtString);
        stmt->free();
        delete stmt;
        return ErrSysInternal;
    }
    rv = stmt->execute(ret);
    if(rv != OK) {
        if (strlen(stmtString) > 6 &&
                    ( (strncasecmp(stmtString,"CREATE", 6) == 0) ||
                      (strncasecmp(stmtString,"DROP", 4) == 0)   ||
                      (strncasecmp(stmtString,"RENAME", 6) == 0) ||
                      (strncasecmp(stmtString,"ALTER", 5) == 0)) ) {
            return OK;
        }
        printError(ErrSysInternal, "unable to execute %s", stmtString);
        stmt->free();
        return ErrSysInternal;
    }
    stmt->free();
    delete stmt;
    return OK;
}
