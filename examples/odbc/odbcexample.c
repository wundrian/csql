/**************************************************************************
 *   Copyright (C) 2008 by www.databasecache.com                          *
 *   Contact : praba_tuty@databasecache.com				  *
 *                                                                        * 
 *   THis program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as Published by * 
 *   the Fre Software Foundation;either version 2 of the License, or      *
 *   (at your option)any later version.                                   *
 *                                                                        *
 *   This program is distributed in the hope that will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, See the         *
 *   GNU General License for more details.                                *
 *                                                                        *
 **************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>

void checkrc(int rc,int line)
{
    if(rc)
    {
	printf("Error %d at line %d\n", rc, line);
	exit(1);
    }
}

int main()
{
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    //Allocate an environment handle
    ret = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
    checkrc(ret,__LINE__);

    //we need ODBC3 support
    SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
	
    //Allocate a Connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
    checkrc(ret,__LINE__);


    //connect to Data source
    ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));
/*
    //connect using unixODBC Driver Manager
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*) 
                     "DSN=mycsql;USER=root;PASSWORD=manager;", SQL_NTS, 
                      outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);
*/
    if(SQL_SUCCEEDED(ret))
    { 
        printf("Connected to CSQL\n");
    }
    else
    {
        printf("error in connection\n");
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);
        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__);
        return 2;
    }

    // Allocation of  statement handle for DDL nad DML Operation
    ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
    checkrc(ret,__LINE__);
 
    // create table 'T1' with two fields, F1 INTEGER AND F2 CHAR.
    SQLCHAR table[200]= "CREATE TABLE T1(F1 INT,F2 CHAR(20))";
   
    ret = SQLPrepare(stmt,table,SQL_NTS);
    checkrc(ret,__LINE__);
   	
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
   	
    printf("Table T1 created\n");

    //Insert 10 Tuples into the table 'T1'
    int id=10;
    char name[20]="THIRU";
    char names[10][20]={"Gopal", "Aruna", "Kanchana", "Vijay", "Ganga",
                       "XieLiang", "Rajesh", "Steve", "Veda", "Jitendra" };


    SQLINTEGER slen = SQL_NTS;
	
    ret  = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?);",SQL_NTS);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&id,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)name,0,&slen);
    checkrc(ret,__LINE__);

    int i,count=0;
    for(i=0;i<10;i++)
    {
        id++;
        strcpy(name,names[i]);
    
        ret = SQLExecute(stmt);
        checkrc(ret,__LINE__);

        ret = SQLTransact(env,dbc,SQL_COMMIT);
        checkrc(ret,__LINE__);
        count++;
    }
    printf("%d Rows inserted\n",count);

	
    //Fetch rows from the table 'T1'
    int id1=10;

    ret = SQLPrepare(stmt,(unsigned char*)"SELECT * FROM T1;",SQL_NTS);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&id1,0,NULL);
    checkrc(ret,__LINE__);
 	
    ret = SQLBindCol(stmt,2,SQL_C_CHAR,name,sizeof(name),NULL);
    checkrc(ret,__LINE__);
	
    count=0;
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
	
    printf("Fetching starts on table T1 :\n");
    while(SQL_SUCCEEDED(ret=SQLFetch(stmt)))
    {
        printf("F1:%d\tF2:%s\n",id1,name);
        count++;
    }
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);

    printf("%d rows fetched\n",count);

    //Delete all the rows from the table 'T1'
    ret = SQLPrepare(stmt,(unsigned char*)"DELETE FROM T1 WHERE F1=?;",SQL_NTS);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&id1,0,NULL);
    checkrc(ret,__LINE__);


    count=0;
    for(i=0;i<10;i++)
    {
       id++;
       ret = SQLExecute(stmt);
       checkrc(ret,__LINE__);
       count++;
    }

    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    printf("%d Rows deleted\n",count);

/*	
    // drop the table 'T1'
    SQLCHAR drop[50]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);

    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    printf("Table T1 dropped\n");
*/
    //Free the statement handle
    ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
    checkrc(ret,__LINE__);

    //Disconnect from the Data source
    ret = SQLDisconnect(dbc);
    checkrc(ret,__LINE__);
    printf("Disconnected from CSQL\n");
   	
    //Free the connection handle
    ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
    checkrc(ret,__LINE__);

    //Free the environment handle
    ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
    checkrc(ret,__LINE__);
    return 0;
}
