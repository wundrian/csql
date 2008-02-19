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
#include <CSql.h>
#include <CacheTableLoader.h>

void printUsage()
{
   printf("Usage: cachetable [-u username] [-p passwd] -t tablename [-r]\n");
   printf("       tablename -> tablename residing in target database which needs to be cached.\n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   printf("       r -> recover all cached tables from the target database.\n");
   return;
  
}

void addToCacheTableFile(char *tablename)
{
    FILE *fp;
    printf("CACHE_TABLE_FILE is %s\n", Conf::config.getCacheTableFile());
    fp = fopen(Conf::config.getCacheTableFile(),"a");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CACHE_TABLE_FILE.\nTable will not be"
                                "recovered in case of crash");
	return;
    }
    
    fprintf(fp, "%s\n", tablename);
    fclose(fp);
}
int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char tablename[IDENTIFIER_LENGTH];
    while ((c = getopt(argc, argv, "u:p:t:r?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'p' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tablename, argv[optind - 1]); opt = 2; break; }
            case '?' : { opt = 10; break; } //print help 
            case 'r' : { opt = 3; break; } //recover all the tables

            default: opt=10; 

        }
    }//while options
    if (opt == 10) {
        printUsage();
        return 0;
    }

    //printf("%s %s \n", username, password);
    if (username[0] == '\0' )
    {
        strcpy(username, "root");
        strcpy(password, "manager");
    }
    DbRetVal rv = OK;
    CacheTableLoader cacheLoader;

    if (opt==2) {
        cacheLoader.setTable(tablename);
        rv = cacheLoader.load(username, password);
        if (rv != OK) exit (1);
        rv = cacheLoader.addToCacheTableFile();
        if (rv != OK) exit (2);
    }else if (opt==3)
    {
        rv = cacheLoader.recoverAllCachedTables(username, password);
        if (rv != OK) exit (1);
    }

/*
    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    Conf::config.getDSN();
    //char* dsn = (char *) "DSN=myodbc3;";
    char dsn[72];
    sprintf(dsn, "DSN=%s;", Conf::config.getDSN());
    printf("DSN VALUE FROM CONFIG=%s\n", dsn);
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    int retValue =0;
    SQLHENV henv; 
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    retValue = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (retValue) exit(1);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    retValue = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
    if (retValue) exit(1);
    retValue = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)dsn, SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
    if (SQL_SUCCEEDED(retValue)) {
        printf("Connected to target database using dsn = %s\n", dsn);
    } else {
        fprintf(stderr, "Failed to connect to target database\n");
        exit (2);
    }


    retValue=SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
    if (retValue) exit(1);
    char stmtBuf[1024];
    sprintf(stmtBuf, "SELECT * FROM %s;", tablename);
    retValue = SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);
    if (retValue) exit(1);
    short totalFields=0;
    retValue = SQLNumResultCols (hstmt, &totalFields);
    if (retValue) exit(1);
    printf("ODBC Retrieved total columns = %d\n", totalFields);

        UWORD                   icol;
        UCHAR                   szColName[IDENTIFIER_LENGTH];
        SWORD                   cbColNameMax;
        SWORD                   pcbColName;
        SWORD                   pfSqlType;
        SQLULEN                 pcbColDef;
        SWORD                   pibScale;
        SWORD                   pfNullable;
        TableDef tabDef;

        icol = 1; cbColNameMax = IDENTIFIER_LENGTH;
        while (icol <= totalFields) {
                retValue = SQLDescribeCol(hstmt, icol, szColName, cbColNameMax,
                                        &pcbColName, &pfSqlType, &pcbColDef,
                                        &pibScale, &pfNullable);
                if (retValue ) exit (2);
 
                printf("Describe Column %s %d %d %d\n", szColName, pcbColName, pfSqlType, pcbColDef);
                icol++;
                tabDef.addField((char*) szColName, AllDataType::convertFromSQLType(pfSqlType), pcbColDef);
        }
    rv = dbMgr->createTable(tablename, tabDef);
    if (rv != OK) { printf("Table creation failed in csql for %s\n", tablename); 
                    conn.close(); SQLDisconnect(hdbc); exit (1); }

    Table *table = dbMgr->openTable(tablename);
    if (table == NULL){ printf("Table creation failed in csql for %s\n", tablename); 
                    conn.close(); SQLDisconnect(hdbc); exit (1); }
    List fNameList = table->getFieldNameList();
    ListIterator fNameIter = fNameList.getIterator();
    FieldInfo *info = new FieldInfo();
    int fcount =1; void *valBuf; int fieldsize=0;
    Identifier *elem = NULL;
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
        if (retValue) exit (12);
    }
    delete info;
    conn.startTransaction();
    retValue = SQLExecute (hstmt);
    if (retValue) exit (13);
    while(true)
    {
        retValue = SQLFetch (hstmt);
        if (retValue) break;
        //TODO::convert odbc to csql for date, time, timestamp

//ACCESSING MEMBERS of above structures...
  //     sDate.year, sDate.month, sDate.day,
    //   sTime.hour, sTime.minute, sTime.second,
      // sTimestamp.year, sTimestamp.month, sTimestamp.day,
       //sTimestamp.hour, sTimestamp.minute, sTimestamp.second, sTimestamp.fraction


        table->insertTuple();
        printf("Inserted tuple\n");
    }
    SQLCloseCursor (hstmt);
    conn.commit();
    //append the tablename in the cache.table
    addToCacheTableFile(tablename);
    conn.close();
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
*/
    
    return 0;
}
