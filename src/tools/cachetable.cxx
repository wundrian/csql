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
#include <sql.h>
#include <sqlext.h>

void printUsage()
{
   printf("Usage: cachetable [-u username] [-p passwd] -t tablename \n");
   printf("       tablename -> tablename residing in target database which needs to be cached.\n");
   printf("       username -> username to connect with csql.\n");
   printf("       passwd -> password for the above username to connect with csql.\n");
   return;
  
}

int main(int argc, char **argv)
{
    char username[IDENTIFIER_LENGTH];
    username [0] = '\0';
    char password[IDENTIFIER_LENGTH];
    password [0] = '\0';
    int c = 0, opt = 10;
    char tablename[IDENTIFIER_LENGTH];
    while ((c = getopt(argc, argv, "u:p:t:?")) != EOF) 
    {
        switch (c)
        {
            case 'u' : { strcpy(username, argv[optind - 1]); opt=10; break; }
            case 'p' : { strcpy(password, argv[optind - 1]); opt=10; break; }
            case 't' : { strcpy(tablename, argv[optind - 1]); opt = 2; break; }
            case '?' : { opt = 10; break; } //print help 
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
    //TODO::Read dsn from the cache.conf file 

    char* dsn = (char *) "DSN=myodbc3;";
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
    SQLPrepare (hstmt, (unsigned char *) stmtBuf, SQL_NTS);

    Connection conn;
    DbRetVal rv = conn.open(username, password);
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = (DatabaseManager*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    Table *table = dbMgr->openTable(tablename);
    if (table == NULL) exit (2);
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
        if (retValue) exit (2);
    }
    delete info;
    conn.startTransaction();
    retValue = SQLExecute (hstmt);
    if (retValue) exit (3);
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
        printf("Inserted tuple\n");
    }
    SQLCloseCursor (hstmt);
    conn.commit();
    conn.close();
    SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
    SQLDisconnect (hdbc);
    SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle (SQL_HANDLE_ENV, henv);
    return 0;
}
