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
DbRetVal CacheTableLoader::addToCacheTableFile()
{
    FILE *fp;
    fp = fopen(Conf::config.getCacheTableFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CACHE_TABLE_FILE.\nTable will not be"
                                "recovered in case of crash");
	return ErrSysInit;
    }
    fprintf(fp, "%s\n", tableName);
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::removeFromCacheTableFile()
{
    FILE *fp;
    fp = fopen(Conf::config.getCacheTableFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CACHE_TABLE_FILE.\nTable will not be"
                                "recovered in case of crash");
	return ErrSysInit;
    }
    //TODO::delete the entry of tableName from the file
    fclose(fp);
    return OK;
}

DbRetVal CacheTableLoader::load(char *username, char *password)
{
    //TODO::take exclusive lock on table

    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return ErrSysInit;
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return ErrSysInit; }

    char dsn[72];
    sprintf(dsn, "DSN=%s;", Conf::config.getDSN());
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    int retValue =0;
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) {printf("Unable to allocate ODBC handle \n"); return ErrSysInit; }
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) {printf("Unable to allocate ODBC handle \n"); return ErrSysInit; }
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printf("Connected to target database using dsn = %s\n", dsn);
    } else {
        fprintf(stderr, "Failed to connect to target database\n");
        return ErrSysInit;
    }

    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) {printf("Unable to allocate ODBC handle \n"); return ErrSysInit; }
    char stmtBuf[1024];
    sprintf(stmtBuf, "SELECT * FROM %s;", tableName);
    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) {printf("Unable to Prepare ODBC statement \n"); return ErrSysInit; }
    short totalFields=0;
    retValue = SQLNumResultCols (hstmt, &totalFields);
    if (retValue) {printf("Unable to retrieve ODBC total columns\n"); return ErrSysInit; }

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
        if (retValue) {printf("Unable to retrieve ODBC column info\n"); return ErrSysInit; }
 
        //printf("Describe Column %s %d %d %d\n", szColName, pcbColName, colType, colLength);
        icol++;
        tabDef.addField((char*) colName, AllDataType::convertFromSQLType(colType), colLength);
    }
    rv = dbMgr->createTable(tableName, tabDef);
    if (rv != OK) { printf("Table creation failed in csql for %s\n", tableName); 
                    conn.close(); SQLDisconnect(hdbc); return rv;}

    Table *table = dbMgr->openTable(tableName);
    if (table == NULL){ printf("Table creation failed in csql for %s\n", tableName); 
                    conn.close(); SQLDisconnect(hdbc); return ErrSysInit; }
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf; int fieldsize=0;
    Identifier *elem = NULL;

    //TODO::support for date, time and timestamp data types. 
    //need to have two buffers as size is different in odbc and csql. 
    //before we insert into csql, we should convert accordingly
    DATE_STRUCT sDate;
    TIME_STRUCT sTime;
    TIMESTAMP_STRUCT sTimestamp;

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
                //TODO::store valBuf with type in list
                fieldsize = sizeof(DATE_STRUCT);
                valBuf = &sDate;
                break;
        }
        retValue = SQLBindCol (hstmt, fcount++, AllDataType::convertToSQLType(info->type),
                               valBuf, fieldsize, NULL);
        if (retValue) {printf("Unable to bind columns in ODBC\n"); return ErrSysInit; }
    }
    delete info;
    conn.startTransaction();
    retValue = SQLExecute (hstmt);
    if (retValue) {printf("Unable to execute ODBC statement\n"); return ErrSysInit; }
    while(true)
    {
        retValue = SQLFetch (hstmt);
        if (retValue) break;
        //TODO::convert odbc to csql for date, time, timestamp
/*
ACCESSING MEMBERS of above structures...
       sDate.year, sDate.month, sDate.day,
       sTime.hour, sTime.minute, sTime.second,
       sTimestamp.year, sTimestamp.month, sTimestamp.day,
       sTimestamp.hour, sTimestamp.minute, sTimestamp.second, sTimestamp.fraction

*/
        table->insertTuple();
    }
    SQLCloseCursor (hstmt);
    conn.commit();
    conn.close();
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
    return OK;
}

DbRetVal CacheTableLoader::reload()
{
    return OK;
}

DbRetVal CacheTableLoader::unload()
{
    return OK;
}

DbRetVal CacheTableLoader::refresh()
{
    return OK;
}

DbRetVal CacheTableLoader::recoverAllCachedTables(char *username, char *password)
{
    FILE *fp;
    fp = fopen(Conf::config.getCacheTableFile(),"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CACHE_TABLE_FILE.\nRecovery Failed.");
	return ErrSysInit;
    }
    //TODO::take exclusive lock on database
    char tablename[IDENTIFIER_LENGTH];
    while(!feof(fp))
    {
        fscanf(fp, "%s\n", tablename);
        printf("Recovering Table : %s\n", tablename);
        setTable(tablename);
        load(username, password);
    }
    fclose(fp);
    return OK;
}