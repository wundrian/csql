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
#include<CacheTableLoader.h>
#include<Util.h>
DbRetVal CacheTableLoader::addToCacheTableFile()
{
    FILE *fp;
    fp = fopen(Conf::config.getTableConfigFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\nTable will not be"
                                "recovered in case of crash");
	return ErrSysInit;
    }
    //TODO::if already table present in the file, it means that the
    //table is replicated. in this case change mode from
    //2 to 3 (repl to replcache)
    fprintf(fp, "%d:%s\n", 1, tableName);
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::removeFromCacheTableFile()
{
    FILE *fp, *tmpfp;
    char tmpFileName[MAX_FILE_PATH_LEN];
    sprintf(tmpFileName, "%s.tmp", Conf::config.getTableConfigFile());
    tmpfp = fopen(tmpFileName,"w");
    if( tmpfp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in TABLE_CONFIG_FILE.\n");
	return ErrSysInit;
    }
    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "csqltable.conf file does not exist");
	return ErrSysInit;
    }
    char tablename[IDENTIFIER_LENGTH];
    int mode;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s\n", &mode, tablename);
        if (strcmp (tablename, tableName) == 0) continue;
        fprintf(tmpfp, "%d:%s\n", mode, tablename);
    }
    fclose(tmpfp);
    fclose(fp);
    char sysCommand[MAX_FILE_PATH_LEN * 2];
    sprintf(sysCommand, "mv %s %s", tmpFileName, Conf::config.getTableConfigFile());
    int ret = system(sysCommand);
    if (ret != 0) 
    {
        printError(ErrSysInit, "Check csqltable.conf file permission. unable to remove %s from file", tableName);
	return ErrSysInit;
    }
    return OK;
}

DbRetVal CacheTableLoader::load(bool tabDefinition)
{
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printError(ErrSysInit, "Auth failed\n"); return ErrSysInit; }
    conn.startTransaction();
    rv = load(dbMgr, tabDefinition);
    conn.commit();
    conn.close();
    return rv;
}

DbRetVal CacheTableLoader::load(DatabaseManager *dbMgr, bool tabDefinition)
{
    char dsn[72];
    sprintf(dsn, "DSN=%s;", Conf::config.getDSN());
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
    DbRetVal rv = OK;
    int retValue =0;
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printDebug(DM_Gateway, "Connected to target database using dsn = %s\n", dsn);
    } else {
        fprintf(stderr, "Failed to connect to target database\n");
        return ErrSysInit;
    }

    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {printError(ErrSysInit, "Unable to allocate ODBC handle \n"); return ErrSysInit; }
    char stmtBuf[1024];
    sprintf(stmtBuf, "SELECT * FROM %s;", tableName);
    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) {printError(ErrSysInit, "Unable to Prepare ODBC statement \n"); return ErrSysInit; }

    if (tabDefinition) {
        short totalFields=0;
        retValue = SQLNumResultCols (hstmt, &totalFields);
        if (retValue) {printError(ErrSysInit, "Unable to retrieve ODBC total columns\n"); return ErrSysInit; }
        UWORD                   icol;
        UCHAR                   colName[IDENTIFIER_LENGTH];
        SWORD                   colNameMax;
        SWORD                   nameLength;
        SWORD                   colType;
        SQLULEN                 colLength;
        SWORD                   scale;
        SWORD                   nullable;
        TableDef tabDef;
        icol = 1; colNameMax = IDENTIFIER_LENGTH;
        while (icol <= totalFields) {
            retValue = SQLDescribeCol(hstmt, icol, colName, colNameMax,
                                        &nameLength, &colType, &colLength,
                                        &scale, &nullable);
            if (retValue) {printError(ErrSysInit, "Unable to retrieve ODBC column info\n"); return ErrSysInit; }
 
            printDebug(DM_Gateway, "Describe Column %s %d %d \n", colName, colType, colLength);
            icol++;
           tabDef.addField((char*) colName, AllDataType::convertFromSQLType(colType), colLength +1);
        }
        rv = dbMgr->createTable(tableName, tabDef);
        if (rv != OK) 
        { 
             printError(ErrSysInit, "Table creation failed in csql for %s\n", tableName); 
             SQLDisconnect(hdbc); 
             return ErrSysInit;
        }
        char columnname[124]; char indexname[124];
        short type; short unique;
        SQLHSTMT hstmtmeta;
        retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmtmeta);
        if (retValue) 
        {
            printError(ErrSysInit, "Unable to allocate ODBC handle \n"); 
            return ErrSysInit; 
        }

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
        while ((retValue = SQLFetch(hstmtmeta)) == SQL_SUCCESS)
        {  //if (type != SQL_TABLE_STAT)
            {   
                printDebug(DM_Gateway, "Column: %-18s Index Name: %-18s unique:%hd type:%hd\n",
                  columnname, indexname, unique, type);
            }
            if (type == 3) {
               HashIndexInitInfo *info = new HashIndexInitInfo();
               info->indType =  hashIndex;
               info->bucketSize = 10007;
               info->list.append(columnname);
               strcpy(info->tableName, tableName);
               char indname[128];
               sprintf(indname, "%s_%s", tableName, indexname);
               rv = dbMgr->createIndex(indname, info);
               if (rv != OK) 
               {
                  printError(ErrSysInit, "Index creation failed in csql for %s\n", tableName); 
                  SQLDisconnect(hdbc); 
                  return ErrSysInit;
               }
               delete info;
           } else {
               printError(ErrSysInit,"CSQL does not support this index type\n");
               SQLDisconnect(hdbc);
               return ErrSysInit;
           }
       }// while meta data fetch for index creation
       SQLCloseCursor (hstmtmeta);
       SQLFreeHandle (SQL_HANDLE_STMT, hstmtmeta);
    }
    Table *table = dbMgr->openTable(tableName);
    if (table == NULL) {
        printError(ErrSysInit,"unable to open table %d\n", tableName);
        dbMgr->closeTable(table);
        if (tabDefinition) dbMgr->dropTable(tableName);
        SQLDisconnect(hdbc);
        return ErrSysInit;
    }
    table->setUndoLogging(false);
    //rv = table->lock(false); //no need to release this lock as it is upgrade from S to X
    if (rv != OK)
    {
        dbMgr->closeTable(table);
        if (tabDefinition) dbMgr->dropTable(tableName);
        SQLDisconnect(hdbc);
        return ErrSysInit;
    }
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf; int fieldsize=0;
    Identifier *elem = NULL;

    BindBuffer *bBuf;
    List valBufList;
    while (fNameIter.hasElement()) {
        elem = (Identifier*) fNameIter.nextElement();
        table->getFieldInfo((const char*)elem->name, info);
        valBuf = AllDataType::alloc(info->type, info->length);
        table->bindFld(elem->name, valBuf);
        fieldsize=0;
        switch( info->type) 
        {
            case typeString:
                fieldsize = info->length;
                break;
            case typeDate:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeDate;
                fieldsize = sizeof(DATE_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
            case typeTime:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeTime;
                fieldsize = sizeof(TIME_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
            case typeTimeStamp:
                bBuf = new BindBuffer();
                bBuf->csql = valBuf;
                bBuf->type = typeTimeStamp;
                fieldsize = sizeof(TIMESTAMP_STRUCT);
                bBuf->targetdb = malloc(fieldsize);
                valBuf = bBuf->targetdb;
                valBufList.append(bBuf);
                break;
        }
        retValue = SQLBindCol (hstmt, fcount++, AllDataType::convertToSQLType(info->type),
                               valBuf, fieldsize, NULL);
        if (retValue) {printError(ErrSysInit, "Unable to bind columns in ODBC\n"); return ErrSysInit; }
    }
    delete info;
    retValue = SQLExecute (hstmt);
    if (retValue) {printError(ErrSysInit, "Unable to execute ODBC statement\n"); return ErrSysInit; }
    while(true)
    {
        retValue = SQLFetch (hstmt);
        if (retValue) break;
        ListIterator bindIter = valBufList.getIterator();
        while (bindIter.hasElement()) {
            bBuf = (BindBuffer*) bindIter.nextElement();
            switch (bBuf->type) {
                case typeDate: {
                    Date *dtCSQL = (Date*) bBuf->csql;
                    DATE_STRUCT *dtTarget = (DATE_STRUCT*) bBuf->targetdb;
                    dtCSQL->set(dtTarget->year,dtTarget->month,dtTarget->day);
                    break;
                }
                case typeTime: {
                    Time *dtCSQL = (Time*) bBuf->csql;
                    TIME_STRUCT *dtTarget = (TIME_STRUCT*) bBuf->targetdb;
                    dtCSQL->set(dtTarget->hour,dtTarget->minute,dtTarget->second);
                    break;
                }
                case typeTimeStamp: {
                    TimeStamp *dtCSQL = (TimeStamp*) bBuf->csql;
                    TIMESTAMP_STRUCT *dtTarget = (TIMESTAMP_STRUCT*) bBuf->targetdb;
                    dtCSQL->setDate(dtTarget->year,dtTarget->month,dtTarget->day);
                    dtCSQL->setTime(dtTarget->hour,dtTarget->minute,dtTarget->second, dtTarget->fraction);
                    break;
                }
            }
        }
        table->insertTuple();
    }
    //TODO::leak:: valBufList and its targetdb buffer
    valBufList.reset();
    dbMgr->closeTable(table);
    SQLCloseCursor (hstmt);
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
    return OK;
}

DbRetVal CacheTableLoader::reload()
{
    DbRetVal rv = unload(false);
    if (rv != OK) return rv;
    rv = load(false);
    return rv;
}

DbRetVal CacheTableLoader::unload(bool tabDefinition)
{
    Connection conn;
    DbRetVal rv = conn.open(userName, password);
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printError(ErrSysInit, "Auth failed\n"); return ErrSysInit; }
    if (!tabDefinition)
    {
        Table *table = dbMgr->openTable(tableName);
        if (table == NULL) { conn.close(); return ErrBadCall; }
        rv = conn.startTransaction();
        if (rv != OK) { dbMgr->closeTable(table); conn.close(); return ErrBadCall; }
        table->truncate();
        conn.commit();
        dbMgr->closeTable(table);
    }
    else
    {
        rv = dbMgr->dropTable(tableName);
    }
    conn.close();

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
    //Note: if connection is not open, configuration veriables may be incorrect

    fp = fopen(Conf::config.getTableConfigFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "cachetable.conf file does not exist");
	return OK;
    }
    conn.close();
    //TODO::take exclusive lock on database
    char tablename[IDENTIFIER_LENGTH];
    int mode;
    rv = OK;
    while(!feof(fp))
    {
        fscanf(fp, "%d:%s\n", &mode, tablename);
        if (mode ==2 )  //just replicated table and not cached
            continue;
        printDebug(DM_Gateway, "Recovering Table from target db: %s\n", tablename);
        setTable(tablename);
        printf("Recovering table %s\n", tablename);
        rv = load();
        if (rv != OK) return rv;
    }
    fclose(fp);
    return OK;
}

