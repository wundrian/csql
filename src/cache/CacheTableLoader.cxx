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
#include<os.h>
#include<CacheTableLoader.h>
#include<TableConfig.h>
#include<Util.h>
#include<SqlConnection.h>
#include<SqlLogConnection.h>
#include<SqlStatement.h>
#include<SqlFactory.h>

DbRetVal CacheTableLoader::load(bool tabDefinition)
{
    AbsSqlConnection *conn = SqlFactory::createConnection(CSqlLog);
    DbRetVal rv = conn->connect(userName, password);
    if (rv != OK) { delete conn; return ErrSysInit; }
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlLog);
    stmt->setConnection(conn);
    SqlLogConnection *logConn = (SqlLogConnection *) conn;
    logConn->setNoMsgLog(true);
    logConn->setNoOfflineLog(true);
    SqlConnection *con = (SqlConnection *) conn->getInnerConnection();
    DatabaseManager *dbMgr = con->getConnObject().getDatabaseManager();
    dbMgr->setCanTakeCheckPoint(false);
    if (tabDefinition == false) {
        rv = hasRecords(dbMgr, tableName);
        if (OK != rv) {
            dbMgr->setCanTakeCheckPoint(true);
            conn->disconnect();
            delete stmt;
            delete conn;
            return ErrNotEmpty;
        }
    }
    conn->beginTrans();
    rv = load(conn, stmt, tabDefinition);
    conn->commit();
    stmt->free();
    dbMgr->setCanTakeCheckPoint(true);
    conn->disconnect();
    delete stmt;
    delete conn;
    return rv;
}
DbRetVal CacheTableLoader::hasRecords(DatabaseManager *dbMgr, const char* tableName)
{
    Table *tbl = dbMgr->openTable(tableName);
    if (tbl == NULL) {
        printError(ErrNotEmpty, "The table '\%s\' is not found", tableName);
        return ErrNotExists;
    }
    if (tbl->numTuples()) {
        printError(ErrNotEmpty, "The table '\%s\' is not empty", tableName);
        dbMgr->closeTable(tbl);
        return ErrNotEmpty;
    }
    dbMgr->closeTable(tbl);
    return OK;
}
DbRetVal CacheTableLoader::connect(SQLHENV &henv, SQLHDBC &hdbc, SQLHSTMT &hstmt, char *dsn, char* stmtBuf)
{
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    int retValue =0;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", dsn);
    } else {
        printError(ErrSysInit, "Failed to connect to target database\n");
        return ErrSysInit;
    }

    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }

    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) {
        printError(ErrSysInit, "Unable to Prepare ODBC statement \n");
        return ErrSysInit;
    }
    return OK;
}

DbRetVal CacheTableLoader::load(AbsSqlConnection *conn, AbsSqlStatement *stmt, bool tabDefinition)
{
    char dsn[IDENTIFIER_LENGTH];
    TDBInfo tdbName = mysql;
    DbRetVal rv = OK;
    
    bool isDSNExist = resolveForDSN(dsn, tdbName, rv);
    if (!isDSNExist) return rv; 
   
    SqlConnection *con = (SqlConnection *) conn->getInnerConnection();
    DatabaseManager *dbMgr = con->getConnObject().getDatabaseManager();
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    int retValue =0;

    /*SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", dsn);
    } else {
        printError(ErrSysInit, "Failed to connect to target database\n");
        return ErrSysInit;
    }

    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
        return ErrSysInit; 
    }

    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) {
        printError(ErrSysInit, "Unable to Prepare ODBC statement \n"); 
        return ErrSysInit; 
    }*/
    char stmtBuf[1024];
    generateCacheTableStatement(stmtBuf);
    connect(henv, hdbc, hstmt, dsn, stmtBuf);
    int nRecordsToFetch = Conf::config.getNoOfRowsToFetchFromTDB();
    int nFetchedRecords = 0;
    SQLUSMALLINT *rowStatus = (SQLUSMALLINT *)
                                malloc(nRecordsToFetch * sizeof(SQLUSMALLINT));
    memset(rowStatus, 0, nRecordsToFetch * sizeof(SQLUSMALLINT));
    SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_BIND_TYPE, SQL_BIND_BY_COLUMN, 0);
    SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_ARRAY_SIZE, (void *) nRecordsToFetch, 0);
    SQLSetStmtAttr(hstmt, SQL_ATTR_ROW_STATUS_PTR, rowStatus, 0 );
    SQLSetStmtAttr(hstmt, SQL_ATTR_ROWS_FETCHED_PTR, &nFetchedRecords, 0 );
    if (tabDefinition) {
        short totalFields=0;
        retValue = SQLNumResultCols (hstmt, &totalFields);
        if (retValue) {
            printError(ErrSysInit, "Unable to retrieve ODBC total columns\n"); 
            return ErrSysInit; 
        }
        logFinest(Conf::logger, "Cache Table noOfFields %hd", totalFields);
        UWORD                   icol=1;
        UCHAR                   colName[IDENTIFIER_LENGTH];
        SWORD                   colNameMax=0;
        SWORD                   nameLength=0;
        SWORD                   colType=0;
        SQLULEN                 colLength = 0;
        SWORD                   scale=0;
        SWORD                   nullable=0;
        colNameMax = IDENTIFIER_LENGTH;
        char columnname[IDENTIFIER_LENGTH];
        short type; short unique;
        SQLHSTMT hstmtmeta;
        retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmtmeta);
        if (retValue)
        {
            printError(ErrSysInit, "Unable to allocate ODBC handle \n");
            return ErrSysInit;
        }
       
        char crtIdxStmt[1024];
        char *ptr=crtIdxStmt;
        HashIndexInitInfo *inf = new HashIndexInitInfo();
        bool isPriIndex = prepareCreateIndexStatement(hstmtmeta, crtIdxStmt, tdbName, inf);
        
        bool iskeyfieldExist=false;
        bool isPKFieldSpecified = false;
        char *name = NULL;
        if((strcmp(fieldName,"")!=0) && (strcmp(fieldName,"NULL")!=0) )
        {
            isPKFieldSpecified = true;
        }
        if ( isPriIndex && ( strcmp(fieldlistVal,"")!=0 ) && 
                                       ( strcmp(fieldlistVal,"NULL") != 0 )) {
            inf->list.resetIter();
            while ( (name=inf->list.nextFieldName()) != NULL) {
                iskeyfieldExist = TableConf::config.isFieldExist(name);
                if(!iskeyfieldExist) { break; }
            }
        } else if (isPriIndex) { iskeyfieldExist = true; }
        if ( isPKFieldSpecified &&  !(TableConf::config.isFieldExist(fieldName)) )
        {
            if ( Conf::config.useTwoWayCache() && 
                             (strcmp(fieldlistVal,"")!=0) && 
                                         (strcmp(fieldlistVal,"NULL")!=0)) 
            {
                printError(ErrSysInit, "Bidirectional caching should have primary key in %s \n", tableName);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
                SQLDisconnect (hdbc);
                SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
                SQLFreeHandle (SQL_HANDLE_ENV, henv);
                delete inf;
                return ErrSysInit;
            }
        }
        if (!iskeyfieldExist && !isPKFieldSpecified )
        {
            if(Conf::config.useTwoWayCache())
            {
                printError(ErrSysInit, "Bidirectional caching fail for no primary key in %s \n", tableName);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
                SQLDisconnect (hdbc);
                SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
                SQLFreeHandle (SQL_HANDLE_ENV, henv);
                delete inf;
                return ErrSysInit;
            }
        } 

        bool isKeyFld=false;
        char crtTblStmt[1024];
        rv = prepareCreateTableStatement(crtTblStmt, hstmt, inf, totalFields,
                                                            tdbName, isKeyFld);
        if (rv != OK) {
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            delete inf;
            return ErrSysInit;
        }
        //printf("table stmt '%s'\n", crtTblStmt);
        if(((strcmp(fieldName,"")!=0) && (strcmp(fieldName,"NULL")!=0))
                                                               && !isKeyFld) {
            printError(ErrSysInit, "Unable to cache Table for %s with key field %s\n", tableName,fieldName);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            delete inf;
            return ErrSysInit;
        }
        rv = stmt->prepare(crtTblStmt);
        if (rv != OK) {
            printError(ErrSysInit, "Unable to prepare create table stmt\n");
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            delete inf;
            return ErrSysInit;
        }   
        int rows = 0;      
        rv = stmt->execute(rows);
        if (rv != OK) {
            printError(ErrSysInit, "Unable to execute create table stmt\n");
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            delete inf;
            return ErrSysInit;
        }   
        logFinest(Conf::logger, "Cache Table: Table Created :%s", crtTblStmt);
       
        //Table is created.
        //Create primary key index if present
        if (isPriIndex && ( iskeyfieldExist || 
           (strcmp(fieldlistVal,"")==0  || strcmp(fieldlistVal,"NULL")== 0))) {
            rv = stmt->prepare(crtIdxStmt);
            if (rv != OK) {
                printError(ErrSysInit, "Unable to prepare create table stmt\n");
                SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
                SQLDisconnect (hdbc);
                SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
                SQLFreeHandle (SQL_HANDLE_ENV, henv);
                delete inf;
                return ErrSysInit;
            }   
            int rows = 0;      
            rv = stmt->execute(rows);
            if (rv != OK) {
                printError(ErrSysInit, "Unable to execute create table stmt\n");
                SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
                SQLDisconnect (hdbc);
                SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
                SQLFreeHandle (SQL_HANDLE_ENV, henv);
                delete inf;
                return ErrSysInit;
            }   
            //printf("Primary index created from create Index stmt\n");
        }
        retValue = SQLCloseCursor(hstmtmeta);
        rv = createIndex(hstmtmeta, tableName, inf, stmt,isPKFieldSpecified);
        if(rv!=OK) {
            dbMgr->dropTable(tableName);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv); 
            delete inf;
            return rv;
        }
        logFinest(Conf::logger, "Cache Table: Index :%s", crtIdxStmt);
        delete inf;
    } // tableDefinition scope finishes here

    else { /***Checking for Table Schema between CSQL and TDB(cachetable -s option)***/
        rv=checkingSchema(hdbc,hstmt,conn,stmt,tdbName);
        if(rv != OK){
            printError(ErrSysInit,"Unable to cache the '%s' table due to schema mismatched.",tableName);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            return ErrSysInit;
        }
    } //***Ends Here

    // Now load the table with records
    stmt->free();

    char insStmt[1024];
    List fNameList;
    fNameList.init();
    SqlStatement *sqlStmt = (SqlStatement *)stmt->getInnerStatement();
    sqlStmt->setConnection(con);
    prepareInsertStatement(sqlStmt, &fNameList, insStmt);
    int totalFields = fNameList.size();
    rv = stmt->prepare(insStmt);
    if (rv != OK) {
        printError(ErrSysInit, "Unable to prepare create table stmt\n");
        SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
        SQLDisconnect (hdbc);
        SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle (SQL_HANDLE_ENV, henv);
        return ErrSysInit;
    }
    sqlStmt->setLoading(true);
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf=NULL; 
    Identifier *elem = NULL;
    void *tembuf=NULL;//For postgre BigInt type
    BindBuffer *bBuf;
    List valBufList;
    int i=0;
    while (fNameIter.hasElement()) {
        elem = (Identifier*) fNameIter.nextElement();
        sqlStmt->getFieldInfo(tableName, (const char*)elem->name, info);
        int size = 0;
        if (info->type == typeString || info->type == typeVarchar) {
            size = nRecordsToFetch * AllDataType::size(info->type,info->length);
        } else {
            size = nRecordsToFetch * AllDataType::size(info->type);
        }
        valBuf = malloc(size);
        os::memset(valBuf,0,size);
        int bindLen = 0;
        if (info->type != typeDate && info->type != typeTime && info->type != typeTimeStamp) {
            if (info->type == typeLongLong && tdbName == postgres)  
                bindLen = 40;
            else
            bindLen =  AllDataType::size(info->type, 
                                  AllDataType::size(info->type, info->length));
        } else {
            switch(info->type) {
            case typeDate: bindLen = sizeof(DATE_STRUCT); break;
            case typeTime: bindLen = sizeof(TIME_STRUCT); break;
            case typeTimeStamp: bindLen = sizeof(TIMESTAMP_STRUCT); break;
            }
        }

        bBuf = (BindBuffer *) SqlStatement::fillBindBuffer(tdbName, info->type, valBuf, bindLen, nRecordsToFetch);
        valBufList.append(bBuf);
        retValue = SQLBindCol (hstmt, fcount, AllDataType::convertToSQL_C_Type(info->type,tdbName), valBuf, bindLen, bBuf->nullData);
        fcount++;
        if (retValue) {
            if(tabDefinition) dbMgr->dropTable(tableName);
            printError(ErrSysInit, "Unable to bind columns in ODBC\n");
            SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
            SQLDisconnect (hdbc);
            SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
            SQLFreeHandle (SQL_HANDLE_ENV, henv);
            return ErrSysInit;
        }
    }
    delete info;
    fNameIter.reset();
    while (fNameIter.hasElement())
        delete ((FieldName *) fNameIter.nextElement());
    fNameList.reset();

    retValue = SQLExecute (hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to execute ODBC statement\n"); 
        SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
        SQLDisconnect (hdbc);
        SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle (SQL_HANDLE_ENV, henv);
        return ErrSysInit; 
    }
    int fldpos=0;
    do {
        //TODO: if SQLFetch return other than record not found error
        //it should drop the table
        retValue = SQLFetchScroll(hstmt, SQL_FETCH_NEXT, 0);
        if (retValue) break;
        for (int row = 0; row < nFetchedRecords; row++) {
            fldpos = 0;
            void *val = NULL;
            ListIterator bindIter = valBufList.getIterator();
            while (bindIter.hasElement()) {
                bBuf = (BindBuffer*) bindIter.nextElement();
                if (bBuf->nullData[row] == SQL_NULL_DATA) {
                    stmt->setNull(fldpos+1);
                } else {
                    val = (void *) ((char *)bBuf->csql + row * bBuf->length);
                    switch (bBuf->type) {
                        case typeString: 
                        {
                            val = (void *) ((char *)bBuf->csql + row * bBuf->length);
                            if( tdbName == postgres) 
                                Util::trimRight((char*)val);
                            break;
                        }  
                        case typeDate: 
                        {
                            val = (void *) ((char *)bBuf->csql + row * sizeof(Date));
                            Date *dtCSQL = (Date*) val;
                            void *tVal = (void *) ((char *)bBuf->targetdb + row * sizeof(DATE_STRUCT));
                            DATE_STRUCT *dtTarget = (DATE_STRUCT*) tVal;
                            dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                            break;
                        }
                        case typeTime:
                        {
                            val = (void *) ((char *)bBuf->csql + row * sizeof(Time));
                            Time *dtCSQL = (Time*) val;
                            void *tVal = (void *) ((char *)bBuf->targetdb + row * sizeof(TIME_STRUCT));
                            TIME_STRUCT *dtTarget = (TIME_STRUCT*) tVal;
                            dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                            break;
                        }
                        case typeTimeStamp:
                        {
                            val = (void *) ((char *)bBuf->csql + row * sizeof(TimeStamp));
                            TimeStamp *dtCSQL = (TimeStamp*) val;
                            void *tVal = (void *) ((char *)bBuf->targetdb + row * sizeof(TIMESTAMP_STRUCT));
                            TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) tVal;
                            dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                            dtCSQL->setTime(dtTarget->hour,dtTarget->minute,dtTarget->second, dtTarget->fraction);
                            break;
                        }
                        case typeLongLong:
                        {
                            val = (void *) ((char *)bBuf->csql + row * sizeof(long long));
                            void *tVal = (void *) ((char *)bBuf->targetdb + row * bBuf->length);
                            if (tdbName == postgres) {
                                sscanf((const char*)tVal,"%lld",(long long*) val);
                            }
                            break;
                        }
                    }
                    SqlStatement::setParamValues(stmt, fldpos+1, bBuf->type, bBuf->length, val);
                }
                fldpos++;
            }
            int rows = 0;
            rv = stmt->execute(rows);
            if (rv != OK) {
                printError(ErrSysInit, "Unable to cache record in CSQL.\n");
                if(tabDefinition) dbMgr->dropTable(tableName);
                SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
                SQLDisconnect (hdbc);
                SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
                SQLFreeHandle (SQL_HANDLE_ENV, henv);
                return ErrSysInit;
            }
            conn->commit();
            conn->beginTrans();
        }
    } while (SQL_SUCCEEDED(retValue) && nFetchedRecords == nRecordsToFetch);
    conn->commit();
    conn->beginTrans();

    //PRABA::one operation per transaction gives the best 
    //performance than 100 /Txn in case of durability
    //TODO::leak:: valBufList and its targetdb buffer
    ListIterator it = valBufList.getIterator();
    while(it.hasElement()) {
        BindBuffer *bb = (BindBuffer *) it.nextElement();
        if (bb->csql) { free(bb->csql); bb->csql = NULL; }
        if (bb->targetdb) { free(bb->targetdb); bb->targetdb = NULL; }
        delete bb; bb = NULL;
    }
    valBufList.reset();
    SQLCloseCursor (hstmt);
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    ::free(rowStatus);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
    logFine(Conf::logger, "Cached Table: %s", tableName);
    return OK;
}

DbRetVal CacheTableLoader::reload()
{
    FILE *fp=NULL;
    DbRetVal rv = unload(false);
    if (rv != OK) return rv;
    //get table cache senarios
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        return OK;
    }
    int mode;
    rv = OK;
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char dsnname[IDENTIFIER_LENGTH];
    while(!feof(fp))
    {
        fscanf(fp, "%d %s %s %s %s %s\n", &mode, tablename,fieldname,condition,field,dsnname);
        if(strcmp(tablename,tableName)==0) break;
    }
    fclose(fp);
    setCondition(TableConf::config.getRealConditionFromFile(condition));
    setFieldName(fieldname);
    setFieldListVal(field);
    setDsnName(dsnname);
    rv = load(false);
    return rv;
}

DbRetVal CacheTableLoader::unload(bool tabDefinition)
{
    AbsSqlConnection *conn = SqlFactory::createConnection(CSqlLog);
    DbRetVal rv = conn->connect(userName, password);
    if (rv != OK) return ErrSysInit;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlLog);
    stmt->setConnection(conn);  
    SqlLogConnection *logConn = (SqlLogConnection *) conn;
    logConn->setNoMsgLog(true);
    char statement[1024];
    if (TableConf::config.isTableCached(tableName) != OK) {
        printError(ErrNotCached, "The table \'%s\' is not cached", tableName);
        conn->disconnect(); 
        delete stmt;
        delete conn;
        return ErrNotCached;
    }
    SqlConnection *con = (SqlConnection *) conn->getInnerConnection();
    DatabaseManager *dbMgr = (DatabaseManager*) con->getConnObject().getDatabaseManager();
    if (dbMgr == NULL) { 
        conn->disconnect(); 
        delete stmt; delete conn;
        printError(ErrSysInit, "Authentication failed\n"); 
        return ErrSysInit; 
    }
    if (!tabDefinition)
    {
        sprintf(statement, "DELETE FROM %s;", tableName);
        SqlStatement *sqlStmt = (SqlStatement*)stmt;
        sqlStmt->setLoading(true);
        rv = stmt->prepare(statement);
        if (rv != OK) { 
            conn->disconnect(); 
            delete stmt; delete conn; 
            return ErrBadCall;
        }
        conn->beginTrans();
        int rows = 0;
        rv = stmt->execute(rows);
        if (rv != OK) { 
            conn->disconnect(); 
            delete stmt; delete conn; 
            return ErrBadCall;
        }
        conn->commit();
    }
    else
    {
        rv = TableConf::config.removeFromCacheTableFile();
        if (rv != OK) { 
            conn->disconnect(); delete stmt; delete conn;
            return ErrBadCall; 
        }
        sprintf(statement, "DROP TABLE %s;", tableName);
        SqlStatement *sqlStmt = (SqlStatement*)stmt;
        sqlStmt->setLoading(true);
        rv = stmt->prepare(statement);
        if (rv != OK) {
            //TableConf::config.addToCacheTableFile(false);
            conn->disconnect(); 
            delete stmt; delete conn; 
            return ErrBadCall;
        }
        int rows = 0;
        rv = stmt->execute(rows);
        if (rv != OK) { 
            //TableConf::config.addToCacheTableFile(false);
            conn->disconnect(); delete stmt; delete conn; 
            return ErrBadCall;
        }
    }
    conn->disconnect();
    delete stmt; delete conn;
    logFine(Conf::logger, "Unloaded Cached Table: %s", tableName);
    return rv;
}

DbRetVal CacheTableLoader::refresh()
{
    return OK;
}

DbRetVal CacheTableLoader::recoverAllCachedTables()
{
    FILE *fp;
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if(rv !=OK) return ErrSysInit;

    //Note: if connection is not open, configuration veriables may be incorrect

    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
        conn.close();
	return OK;
    }
    conn.close();
    //TODO::take exclusive lock on database
    char tablename[IDENTIFIER_LENGTH];
    char fieldname[IDENTIFIER_LENGTH];
    char condition[IDENTIFIER_LENGTH];
    char field[IDENTIFIER_LENGTH];
    char dsnname[IDENTIFIER_LENGTH];
    
    int mode;
    int scanItems=0;
    rv = OK;
    while(!feof(fp))
    {
        scanItems = fscanf(fp, "%d %s %s %s %s %s\n", &mode, tablename,fieldname,condition,field,dsnname);
        if (scanItems != 6) {
            tablename[0]='\0';
            printf("There is no table to be cached.\n");
            return OK;
        }
        if (!TableConf::config.isTableCached(mode)) continue;
        printDebug(DM_Gateway, "Recovering Table from target db: %s\n", tablename);
        setCondition(TableConf::config.getRealConditionFromFile(condition));
        if( (strcmp(Conf::config.getDSN(),dsnname)!=0) ){
		     setDsnName(dsnname);
             setTable(tablename);
             setFieldName(fieldname);
             setFieldListVal(field);
             printf("Recovering table %s %s %s\n", tablename,condition,field);
             rv = load();
             if (rv != OK) { fclose(fp); return rv; }
        } else {
             setDsnName(Conf::config.getDSN());
             setTable(tablename);
             setFieldName(fieldname);
             setFieldListVal(field);
             printf("Recovering table %s %s %s\n", tablename,condition,field);
             rv = load();
             if (rv != OK) { fclose(fp); return rv; }
        }
        logFine(Conf::logger, "Recovering Table from target db:%s", tablename);
    }
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::createIndex(SQLHSTMT hstmtmeta, char *tableName, HashIndexInitInfo *inf,AbsSqlStatement *stmt,bool isPKFieldSpecified)
{
        bool isKeyFld= false;
        int retValue = 0;
        char columnname[IDENTIFIER_LENGTH];
        char indexname[IDENTIFIER_LENGTH];
        short type;
        short unique;
        char *name = NULL;
        DbRetVal rv = OK;
        retValue = SQLStatistics(hstmtmeta, NULL, 0, NULL, SQL_NTS,
                    (SQLCHAR*) tableName, SQL_NTS, SQL_INDEX_ALL, SQL_QUICK);
        retValue = SQLBindCol(hstmtmeta, 4, SQL_C_SHORT,
                          &unique, 2, NULL);
        retValue = SQLBindCol(hstmtmeta, 6, SQL_C_CHAR,
                          indexname, 129, NULL);
        retValue = SQLBindCol(hstmtmeta, 7, SQL_C_SHORT,
                          &type, 2, NULL);
        retValue = SQLBindCol(hstmtmeta, 9, SQL_C_CHAR,
                          columnname, 129,NULL);
        List indexList;
        bool isSecondTime = false;
        CacheIndexInfo *info=NULL;
        while ((retValue = SQLFetch(hstmtmeta)) == SQL_SUCCESS) {
            printDebug(DM_Gateway, "Column: %-18s Index Name: %-18s unique:%hd type:%hd\n", columnname, indexname, unique, type);

            if (type == 3) {
                bool isFldAdd = false;
                ListIterator iter = indexList.getIterator();
                iter.reset();
                while (iter.hasElement()) {
                    CacheIndexInfo *indInfo = (CacheIndexInfo *)iter.nextElement();
                    if(0 == strcmp( indInfo->indexName, indexname))
                    {
                         indInfo->fieldNameList.append(columnname);
                         isFldAdd = true;
                    }
                }
                if(!isFldAdd){
                    info = new CacheIndexInfo();
                    info->fieldNameList.append(columnname);
                    strcpy(info->indexName, indexname);
                    indexList.append(info);
                    isSecondTime = true;
                }
            }
        }
        ListIterator iter = indexList.getIterator();
        iter.reset();
        int noOfPkfield = inf->list.size();
        char *fName=NULL; 
        char *cptr = NULL;
        while (iter.hasElement()) {
            cptr = columnname;
            bool isFieldExistInCondition = false;
            bool isPrimary=false;
            CacheIndexInfo *indInfo = (CacheIndexInfo *)iter.nextElement();
            int noOfFld= indInfo->fieldNameList.size();
            indInfo->fieldNameList.resetIter();
            while ((fName = indInfo->fieldNameList.nextFieldName())!=NULL) {
                if(( 1 == noOfFld) && (0 == strcmp(fName,fieldName))) { 
                    isKeyFld=true; 
                }
                inf->list.resetIter();
                while ((name=inf->list.nextFieldName())!=NULL) 
                {
                    if(0==strcmp(fName,name)) {  isPrimary = true;  break;  }
                    isPrimary = false;
                }
		        if (!TableConf::config.isFieldExist(fName) && 
                                     ( (strcmp(fieldlistVal,"")!=0) && 
                                          (strcmp(fieldlistVal,"NULL")!=0) )) { 
                     isFieldExistInCondition =true; 
                     continue; 
                }
                sprintf(cptr, "%s ,",fName);
                cptr += strlen(cptr);
            }
            if(isFieldExistInCondition) continue;
            cptr -=1;
            *cptr = '\0'; 
            if (isPrimary) { continue; }
            char crtIdxStmt[1024];
            char indname[128];
            sprintf(indname, "%s_%s", tableName, indInfo->indexName);
            sprintf(crtIdxStmt, "CREATE INDEX %s on %s(%s) HASH SIZE 10007;", indname, tableName, columnname);
            //printf("create index stmt \n'%s'\n", crtIdxStmt);
            rv = stmt->prepare(crtIdxStmt);
            if (rv != OK) {
                printError(ErrSysInit, "Unable to prepare create table stmt\n");
                return ErrSysInit;
            }
            int rows = 0;
            rv = stmt->execute(rows);
            if (rv != OK) {
                printError(ErrSysInit, "Unable to execute create table stmt\n");
                return ErrSysInit;
            }
            //delete indInfo;
        }// while meta data fetch for index creation

        iter.reset();
        while (iter.hasElement()) delete (CacheIndexInfo *) iter.nextElement();
        indexList.reset();

        SQLCloseCursor (hstmtmeta);
        SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
        if( !isKeyFld && isPKFieldSpecified) {
            if(shouldForce) {
                char frcIndStmt[1024];
                char indname[128];
                sprintf(indname, "%s_%s", tableName, "keyInd");
                sprintf(frcIndStmt, "CREATE INDEX %s on %s(%s) HASH;", indname, tableName, fieldName);
                rv = stmt->prepare(frcIndStmt);
                if (rv != OK) {
                    printError(ErrSysInit, "Unable to prepare create table stmt\n");
                    return ErrSysInit;
                }
                int rows = 0;
                rv = stmt->execute(rows);
                if (rv != OK) {
                    printError(ErrSysInit, "Unable to execute create table stmt\n");
                    return ErrSysInit;
                }
            } else {
                printError(ErrSysInit, "Unable to cache Table for %s with key field %s\n", tableName,fieldName);
                return ErrSysInit;
            }
        }
     return OK;
}

// Schema matching between CSQL and TDB table.(cachetable -t <tablename> -s)
DbRetVal CacheTableLoader::checkingSchema(SQLHDBC hdbc,SQLHSTMT hstmt, AbsSqlConnection *conn, AbsSqlStatement *stmt,TDBInfo tdbName)
{
    DbRetVal rv=OK;
    int noOfPrimaryKey=0;
    int retValue=0;
    int csqlFields=0;

    SQLSMALLINT tdbFields=0;
    SQLHSTMT hstmtmeta;
    char columnname[IDENTIFIER_LENGTH];

    UWORD                   icol=1;
    UCHAR                   colName[IDENTIFIER_LENGTH];
    SWORD                   colNameMax=0;
    SWORD                   nameLength=0;
    SWORD                   colType=0;
    SQLULEN                 colLength = 0;
    SWORD                   scale=0;
    SWORD                   nullable=0;
    colNameMax = IDENTIFIER_LENGTH;

    SqlConnection *con = (SqlConnection *) conn->getInnerConnection();
    DatabaseManager *dbMgr = con->getConnObject().getDatabaseManager();

    SqlStatement *sqlStmt = (SqlStatement *)stmt->getInnerStatement();
    sqlStmt->setConnection(con);

    List fNameList ;
    fNameList = sqlStmt->getFieldNameList(tableName, rv);
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    Identifier *elem = NULL;

    retValue=SQLNumResultCols(hstmt, &tdbFields);
    if(retValue) {
       printError(ErrSysInit, "Unable to retrieve ODBC total columns.\n");
       SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
       return ErrSysInit;
    }
    // CSQL Table fields 
    fNameList = sqlStmt->getFieldNameList(tableName, rv);
    csqlFields = fNameList.size();
    // noOfFields in both the database are same or not. 
    if(tdbFields!=csqlFields){
        printError(ErrSysInit,"Number of fields between CSQL and TDB are not equal.");
        SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
        return ErrSysInit;
    }
    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmtmeta);
    if(retValue){
        printError(ErrSysInit, "Unable to allocate ODBC handle. \n");
        SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
        return ErrSysInit;
    }
    retValue=SQLPrimaryKeys(hstmtmeta, NULL, SQL_NTS, NULL, SQL_NTS, (SQLCHAR*) tableName, SQL_NTS);
    retValue = SQLBindCol(hstmtmeta, 4, SQL_C_CHAR,columnname, 129,NULL);

    while(icol<=tdbFields){
        retValue = SQLDescribeCol(hstmt, icol, colName, colNameMax,
                             &nameLength, &colType, &colLength,
                             &scale, &nullable);//TDB Field Name
        if(retValue){
            printError(ErrSysInit, "Unable to retrieve ODBC column info.\n");
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            return ErrSysInit;
        }
        Util::str_tolower((char*)colName);
        elem = (Identifier*) fNameIter.nextElement();
        sqlStmt->getFieldInfo(tableName, (const char*)elem->name, info);
        char fldName[20];
        int isNull;
        int isPrimary;
        rv = stmt->getParamFldInfo(icol,info);
        char *name=(info->fldName);//Getting field name for CSQL table.
        Util::str_tolower((char*)name);
        if(strcmp(name,(char *)colName) != 0){ //Field name matching between CSQL and TDB.
            printError(ErrSysInit,"CSQL's '%s' field did not match with TDB's '%s' field.\n",name,(char*)colName);
            SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
            return ErrSysInit;
        }
     
        // DataType matching between CSQL and TDB 
        char ptr[IDENTIFIER_LENGTH]; ptr[0]='\0';
        char ptr1[IDENTIFIER_LENGTH]; ptr1[0]='\0';

        sprintf(ptr,"%s",AllDataType::getSQLString (AllDataType::convertFromSQLType(colType,colLength,scale,tdbName)));
        sprintf(ptr1,"%s",AllDataType::getSQLString(info->type));//CSQL Type 
        if(strcmp(ptr,ptr1)!=0){
           printError(ErrSysInit,"DataType did not match for '%s' field in CSQL.\n",name);
           SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
           return ErrSysInit;
        }
        
       // Primary Key checking 
       bool tdbPKey=false;
       if(SQLFetch( hstmtmeta ) == SQL_SUCCESS) tdbPKey=true;
       if(tdbPKey && (!info->isPrimary))
       printf("Warning: In CSQL, The %s's '%s' field should have Primery Key constraint.\n",tableName,name);
       if((!tdbPKey) && info->isPrimary)
           printf("Warning: In TDB, The %s's '%s' field should have Primary Key constraint.\n",tableName,colName);
       
       // NotNull Checking 
       bool isCsqlNotNull=false;
       bool isTdbNotNull=false;
       if(tdbName==mysql){
           if(info->isNull && nullable)
           printf("Warning: In TDB, The %s's '%s' field should have a NOT NULL constraint.\n",tableName,colName);
           if((!info->isNull) && (!nullable))
               printf("Warning: In CSQL, The %s's '%s' field should have a NOT NULL constraint.\n",tableName,name);
       }
       icol++;
   }
   return OK;
}

DbRetVal CacheTableLoader::cacheAllTablesFromDs(char *dsnName,bool tableDefinition, bool isDirect,char *username, char *password)
{
    char dsn[72];
    DbRetVal rv = OK;
    FILE *fp;
    fp = fopen(Conf :: config.getDsConfigFile(),"r");
    if(fp==NULL) {
        printError(ErrSysInit, "csqlds.conf file does not exist");
        return ErrSysInit;
    }
    char dsnId[IDENTIFIER_LENGTH]; dsnId[0]='\0';
    char user[IDENTIFIER_LENGTH]; user[0] = '\0';
    char passwd[IDENTIFIER_LENGTH]; passwd[0] = '\0';
    char tdb[IDENTIFIER_LENGTH]; tdb[0]='\0';
    unsigned int mode;
    bool isCached=false;

    // If -d option is disable, the If statementn will true. 
    if(strcmp(dsnName,"")==0) {
        strcpy(dsnName, Conf::config.getDSN());
    }
    bool isDSNExist=false;
    while(!feof(fp)) {
       fscanf(fp,"%s %s %s %s\n",dsnId,user,passwd,tdb);
       if(strcmp(dsnId,dsnName)==0) {
           if( strcmp(user,"NULL")!=0 && strcmp(passwd,"NULL")!=0) {
               sprintf(dsn,"DSN=%s;UID=%s;PWD=%s;",dsnName,user,passwd);
               isDSNExist=true;
               break;
           }else{
               sprintf(dsn,"DSN=%s;",dsnName);
               isDSNExist=true;
               break;
           }
       }
    }
     if(!isDSNExist) {
       printError(ErrNotExists,"Entries is not present in the csqlds.conf file\n");
       fclose(fp);
       return ErrNotExists;
    }
    fclose(fp);
    
    TDBInfo tdbName=mysql;
    if (strcasecmp(tdb,"mysql") == 0) tdbName=mysql;
    else if (strcasecmp(tdb,"postgres")==0) tdbName=postgres;
    else printError(ErrNotFound,"Target Database Name is not properly set.Tdb name could be MySql and Postgres.\n");
    logFine(Conf::logger, "TDB Name:%s\n", tdb);

    // The ODBC section in intended to get all the tables from TDB,
    // what SQLTables() is doing that.

    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    int retValue =0;
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLSMALLINT columns;
    char table[IDENTIFIER_LENGTH][IDENTIFIER_LENGTH];
    int counter=0;
    char buf[IDENTIFIER_LENGTH];
    int row = 0;
    SQLINTEGER indicator[ 5 ];
     int colPos;//Only to bind table name filed.

    CacheTableLoader cacheLoader;

    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }
    // We want ODBC 3 support 
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
     if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", dsn);
    }else{
        printError(ErrSysInit, "Failed to connect to target database\n");
        return ErrSysInit;
    }
    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {
        printError(ErrSysInit, "Unable to allocate ODBC handle \n");
        return ErrSysInit;
    }
    if(tdbName == mysql){
        colPos=3;
        // User name is required in upper case for the SQLTables()'s  4th parameter 
        Util::str_toupper((char*)user);
        retValue=SQLTables(hstmt,NULL, 0, (SQLCHAR*)user, SQL_NTS, NULL, 0, (SQLCHAR*)"TABLE", SQL_NTS);
        if(retValue){
            printError(ErrSysInit, "Unable to retrieve list of tables\n");
            return ErrSysInit;
        }
        // Binding Column for 3rd parameter to get Table name. 
        retValue=SQLBindCol(hstmt,3, SQL_C_CHAR,buf,sizeof(buf),NULL);
        if(retValue){
            printError(ErrSysInit,"Unable to BindCol\n");
            return ErrSysInit;
        }
        // For Postgres DB , SQLTables() retrieves all system and metadata tables,along with User defined table.
        // So Here is a another option to fetch the user defined tables only 
    }else if(tdbName==postgres){
        SQLCHAR table[200]="SELECT table_name FROM information_schema.tables  WHERE table_schema NOT IN ('pg_catalog','information_schema');";
        retValue=SQLPrepare(hstmt,table,SQL_NTS);
        if(retValue){
            printError(ErrSysInit,"Unable to Prapare the statement\n");
            return ErrSysInit;
        }
        retValue = SQLBindCol(hstmt,1,SQL_C_CHAR,buf,sizeof(buf),NULL);
        if(retValue){
            printError(ErrSysInit,"Unable to bind the column\n");
            return ErrSysInit;
        }
        retValue = SQLExecute(hstmt);
        if(retValue){
            printError(ErrSysInit,"Unable to execute\n");
            return ErrSysInit;
        }
    }

    while(SQL_SUCCEEDED(retValue = SQLFetch(hstmt))){
        // copy Buffer value 
        //strcpy(&table[counter][0],buf);
        cacheLoader.setDsnName(dsnName);
        TableConf::config.setDsnName(dsnName);
        cacheLoader.setConnParam(username, password);
        TableConf::config.setConnParam(username, password);
        // Check table is cached or not 
        mode = TableConf::config.getTableMode(buf);
        cacheLoader.setTable(buf);
        TableConf::config.setTable(buf);
        isCached = TableConf::config.isTableCached(mode);
        if(isCached){
            printf("Warning: Table '%s' is already cached.\n",buf);
        }else{
             rv = cacheLoader.load(tableDefinition);
             if(rv != OK){
                 printf("Warning: Table '%s' is present in CSQL locally.\n",buf);
             }else{
                  TableConf::config.addToCacheTableFile(isDirect);
                  printf("Cached Table:%s\n",buf);
                  TableConf::config.init();
             }   
        }
        counter++;
    }
    // Checking couter value 
    if(counter==0) 
    printf("There is no table present in Target Database.\n");
    retValue=SQLCloseCursor(hstmt);
    if(retValue){
        printError(ErrSysInit,"Unable to close the cursor\n");
        return ErrSysInit;
    }
    retValue=SQLTransact(henv,hdbc,SQL_COMMIT);
    if(retValue){
        printError(ErrSysInit,"Unable to commit the transaction\n");
        return ErrSysInit;
    }
    retValue = SQLFreeHandle(SQL_HANDLE_STMT,hstmt);
    if(retValue){
        printError(ErrSysInit,"Unable to free statement handle\n");
        return ErrSysInit;
    }
    retValue = SQLDisconnect(hdbc);
    if(retValue){
         printError(ErrSysInit,"Unable to disconnect from DS handle\n");
         return ErrSysInit;
    }
    retValue = SQLFreeHandle(SQL_HANDLE_DBC,hdbc);
    if(retValue){
        printError(ErrSysInit,"Unable to free connection handle\n");
        return ErrSysInit;
    }
    retValue = SQLFreeHandle(SQL_HANDLE_ENV,henv);
    if(retValue){
        printError(ErrSysInit,"Unable to free environment handle\n");
        return ErrSysInit;
    }
    return OK;
}

bool CacheTableLoader::resolveForDSN(char *dsn, TDBInfo &tdbName, DbRetVal &rv)
{
    char dsnId[IDENTIFIER_LENGTH]; dsnId[0]='\0';
    char user[IDENTIFIER_LENGTH]; user[0] = '\0';
    char passwd[IDENTIFIER_LENGTH]; passwd[0] = '\0';
    char tdb[IDENTIFIER_LENGTH]; tdb[0]='\0';
    FILE *fp;

    fp = fopen(Conf::config.getDsConfigFile(),"r");
    if(fp==NULL) {
        printError(ErrSysInit, "csqlds.conf file does not exist");
        rv = ErrSysInit;
        return false;
    }

    // STARTs Here: 
    // DSN, user and password value is read here from csql.conf file and 
    // csqlds.conf file.
    // it's true if -d option is specified and the DSN value not matched with 
    // csql.conf's DSN.
    if(strcmp(dsnName,"")==0) strcpy(dsnName, Conf::config.getDSN());

    bool isDSNExist=false;
    while(!feof(fp)) {
        fscanf(fp,"%s %s %s %s\n",dsnId,user,passwd,tdb);
    if(strcmp(dsnId,dsnName)==0) {   // Both the DSN is matched here
        if(strcmp(user,"NULL")!=0 && strcmp(passwd,"NULL")!=0) {
                sprintf(dsn,"DSN=%s;UID=%s;PWD=%s;",dsnName,user,passwd);
                isDSNExist=true;
                break;
            } else {
                sprintf(dsn,"DSN=%s;",dsnName);
                isDSNExist=true;
                break;
            }
        }
    }
    if(!isDSNExist) {
        printError(ErrNotExists,"Entries is not present in the csqlds.conf file\n");
        fclose(fp);
        rv = ErrNotExists;
        return false;
    }
    fclose(fp);
    if (strcasecmp(tdb,"mysql") == 0) tdbName=mysql;
    else if (strcasecmp(tdb,"postgres")==0) tdbName=postgres;
    else {
        printError(ErrNotFound," Target Database Name is not properly set.Tdb name could be mysql, postgres\n");
        rv = ErrNotFound;
        return false;
    }
    logFine(Conf::logger, "TDB Name:%s\n", tdb);
    return isDSNExist;
}

void CacheTableLoader::generateCacheTableStatement(char *stmtBuf)
{
    if(((strcmp(conditionVal,"")==0) || (strcmp(conditionVal,"NULL")==0)) && 
       ((strcmp(fieldlistVal,"")==0) || (strcmp(fieldlistVal,"NULL")==0)))
    {
       sprintf(stmtBuf, "SELECT * FROM %s;", tableName);
    }
    else if(((strcmp(conditionVal,"")!=0) || (strcmp(conditionVal,"NULL")!=0)) && 
            ((strcmp(fieldlistVal,"")==0) || (strcmp(fieldlistVal,"NULL")==0)))
    {
       sprintf(stmtBuf,"SELECT * FROM %s where %s;",tableName,conditionVal);

    }
    else if(((strcmp(conditionVal,"")==0) || (strcmp(conditionVal,"NULL")==0)) && 
            ((strcmp(fieldlistVal,"")!=0) || (strcmp(fieldlistVal,"NULL")!=0)))
    {
        sprintf(stmtBuf,"SELECT %s FROM %s;",fieldlistVal,tableName);
    }
    else {
        sprintf(stmtBuf,"SELECT %s FROM %s where %s;",fieldlistVal,tableName,conditionVal);
    }
    logFinest(Conf::logger, "Cache Table Stmt %s", stmtBuf);
}

bool CacheTableLoader::prepareCreateIndexStatement(SQLHSTMT hstmtmeta, 
                                    char *crtIdxStmt, TDBInfo tdbName, HashIndexInitInfo *inf)
{
    char columnname[IDENTIFIER_LENGTH];
    char indexname[IDENTIFIER_LENGTH];
    int retValue=SQLPrimaryKeys(hstmtmeta, NULL, SQL_NTS, NULL, SQL_NTS, 
                                               (SQLCHAR*) tableName, SQL_NTS);
    retValue = SQLBindCol(hstmtmeta, 4, SQL_C_CHAR,columnname, 129,NULL);
    char *ptr=crtIdxStmt;
    sprintf(ptr, "CREATE INDEX %s_PRIMARY on %s ( ", tableName, tableName);
    ptr += strlen(ptr);
    bool isPriIndex=false;
    char indname[IDENTIFIER_LENGTH];
    if(SQLFetch( hstmtmeta ) == SQL_SUCCESS)
    {
        Util::str_tolower(columnname);
        inf->list.append(columnname);
        sprintf(ptr, "%s ", columnname);
        ptr += strlen(ptr);
        while ( SQLFetch( hstmtmeta ) == SQL_SUCCESS ) {
            Util::str_tolower(columnname);
            inf->list.append(columnname);
            sprintf(ptr, ", %s ", columnname);
            ptr += strlen(ptr);
        }
        sprintf(ptr, ") PRIMARY SIZE 10007;");
        inf->indType =  hashIndex;
        inf->bucketSize = 10007;
        inf->isUnique = true; inf->isPrimary = true;
        strcpy(inf->tableName, tableName);
        strcpy(indexname,"PRIMARY");
        sprintf(indname, "%s_%s", tableName, indexname);
        isPriIndex=true;
    }
    return isPriIndex;
}

DbRetVal CacheTableLoader::prepareCreateTableStatement(char *crtTblStmt, SQLHSTMT hstmt, 
                  HashIndexInitInfo *inf, int totalFields, TDBInfo tdbName, bool &isKeyFld)
{
    DbRetVal rv = OK;
    UWORD icol=1;
    UCHAR colName[IDENTIFIER_LENGTH];
    SWORD colNameMax=IDENTIFIER_LENGTH;
    SWORD nameLength=0;
    SWORD colType=0;
    SQLULEN colLength = 0;
    SWORD scale=0;
    SWORD nullable=0;
    int retValue = 0;
    bool isNullfld=false;
    bool firstFld = true;
    char *name = NULL;

    char *ptr = crtTblStmt;
    sprintf(ptr, "CREATE TABLE %s ( ", tableName);
    ptr += strlen(ptr);
    while (icol <= totalFields) {
        retValue = SQLDescribeCol(hstmt, icol, colName, colNameMax,
                                         &nameLength, &colType, &colLength,
                                                            &scale, &nullable);
        if (retValue) {
            printError(ErrSysInit, "Unable to retrieve ODBC column info\n");
            return ErrSysInit;
        }
        Util::str_tolower((char*)colName);
        printDebug(DM_Gateway, "Describe Column %s %d %d %d %d\n", 
                      colName, colType, colLength, scale, nullable);
        logFinest(Conf::logger, "Describe Column colName:%s \
                                colType:%d colLen:%d scale:%d nullable:%d\n", 
                                colName, colType, colLength, scale, nullable);
        icol++;
        if(strcmp((char*)colName,fieldName)== 0)
        {
            isKeyFld=true;
            isNullfld=true;
        }
        bool isPriFld=false;
        if (nullable) {
            inf->list.resetIter();
            while ((name=inf->list.nextFieldName())!=NULL) {
                if(0==strcmp((char*)colName,name)) {
                    if (firstFld) {
                        firstFld = false;
                        sprintf(ptr, "%s %s", colName, AllDataType::getSQLString(
                                                       AllDataType::convertFromSQLType(
                                                       colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY)
                        {
                            sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                        } else { sprintf(ptr, " NOT NULL"); }
                            ptr += strlen(ptr);
                    } else {
                        sprintf(ptr, ", %s %s", colName, AllDataType::getSQLString(
                                                         AllDataType::convertFromSQLType(
                                                       colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY)
                        {
                            sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                        } else { sprintf(ptr, " NOT NULL"); }
                        ptr += strlen(ptr);
                    }
                    //tabDef.addField((char*)colName, AllDataType::convertFromSQLType(
                    //                                  colType,colLength,scale,tdbName), 
                    //                                  colLength +1, NULL, true);
                    isPriFld=true;
                    break;
                }
            }
            if(!isPriFld) {
                if(!isNullfld) {
                    if (firstFld) {
                        firstFld = false;
                        sprintf(ptr, "%s %s", colName, AllDataType::getSQLString(
                                                       AllDataType::convertFromSQLType(
                                                       colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                            sprintf(ptr, "(%u)",(unsigned int)colLength+1);
                            ptr += strlen(ptr);
                        }
                    } else {
                        sprintf(ptr, ", %s %s", colName, AllDataType::getSQLString(
                                                         AllDataType::convertFromSQLType(
                                                         colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                            sprintf(ptr, "(%u)",(unsigned int)colLength+1);
                            ptr += strlen(ptr);
                        }
                    }
                    //tabDef.addField((char*)colName, AllDataType::convertFromSQLType(
                    //                                colType,colLength,scale,tdbName), colLength+1);
                } else {
                    if (firstFld) {
                        firstFld = false;
                        sprintf(ptr, "%s %s", colName, AllDataType::getSQLString(
                                                       AllDataType::convertFromSQLType(
                                                       colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                            sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                        } else { sprintf(ptr, " NOT NULL"); }
                        ptr += strlen(ptr);
                    } else {
                        sprintf(ptr, ", %s %s", colName, AllDataType::getSQLString(
                                                         AllDataType::convertFromSQLType(
                                                         colType,colLength,scale,tdbName)));
                        ptr += strlen(ptr);
                        if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                            sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                        } else { sprintf(ptr, " NOT NULL"); }
                        ptr += strlen(ptr);
                    }
                    //tabDef.addField((char*)colName, AllDataType::convertFromSQLType(
                    //                                  colType,colLength,scale,tdbName), 
                    //                                  colLength+1, NULL, true);
                    isNullfld=false;
                }
            }
        } else {
            if (firstFld) {
                firstFld = false;
                sprintf(ptr, "%s %s", colName, AllDataType::getSQLString(
                                               AllDataType::convertFromSQLType(
                                               colType,colLength,scale,tdbName)));
                ptr += strlen(ptr);
                if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                    sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                } else { sprintf(ptr, " NOT NULL"); }
                ptr += strlen(ptr);
            } else {
                sprintf(ptr, ", %s %s", colName, AllDataType::getSQLString(
                                                 AllDataType::convertFromSQLType(
                                                 colType,colLength, scale, tdbName)));
                ptr += strlen(ptr);
                if (colType == SQL_CHAR || colType == SQL_VARCHAR || colType == SQL_BINARY) {
                    sprintf(ptr, "(%u) NOT NULL",(unsigned int)colLength+1);
                } else { sprintf(ptr, " NOT NULL"); }
                ptr += strlen(ptr);
            }
            //tabDef.addField((char*)colName, AllDataType::convertFromSQLType(
            //                                  colType,colLength,scale, tdbName), 
            //                                  colLength +1, NULL, true);
        }
    }
    sprintf(ptr, ");");
    ptr += strlen(ptr);
    //printf("table stmt '%s'\n", crtTblStmt);
    return rv;
}

void CacheTableLoader::prepareInsertStatement(AbsSqlStatement *stmt, List *fNameList, char *insStmt)
{
    DbRetVal rv = OK;
    char *ptr = insStmt;
    sprintf(ptr,"INSERT INTO %s VALUES(", tableName);
    ptr += strlen(ptr);
    bool firstFld = true;
    SqlStatement *sqlStmt = (SqlStatement *)stmt;
    *fNameList = sqlStmt->getFieldNameList(tableName, rv);
    int noOfFields = fNameList->size();
    while (noOfFields--) {
        if (firstFld) {
            firstFld = false;
            sprintf(ptr,"?", tableName);
            ptr += strlen(ptr);
        } else {
            sprintf(ptr, ",?");
            ptr += strlen(ptr);
        }
    }
    sprintf(ptr, ");");
    ptr += strlen(ptr);
}
