#include<CSql.h>
#include<sql.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TS 1000

int main(int argc, char **argv)
{
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret;
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;
   
    SQLHDBC adDbc;
    SQLHSTMT adStmt;

    struct timeval timeout;
    struct timeval timeStamp;
    char msgBuf[25];
 
    if (argv[1] == NULL) {
        fprintf(stderr, "Usage: csqlInsert <o/p file>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "a");

   // Aloocate an environment handle
    ret=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
  
    //we need odbc3 support
    SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);

    //ALLOCATE A Connection handle
    ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
    ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&adDbc);

    // connect to the DSN mydsn
    ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));
  
    if(SQL_SUCCEEDED(ret)) printf("\nConnected to the csql Data Source..\n");
    else
    {
        printf("error in conenction\n");
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        return 1;
    }
    ret = SQLConnect (adDbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=ADAPTER;SERVER=localhost;PORT=5678;", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

    if(SQL_SUCCEEDED(ret)) printf("\nConnected to the msql Data Source..\n");
    else
    {
        printf("error in conenction\n");
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        return 1;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
    ret = SQLAllocHandle(SQL_HANDLE_STMT,adDbc,&adStmt);
    int rnd = 0;
    ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO soakTable VALUES(1234,?,93333993,'CSQL_LAKSHYA');",SQL_NTS); 
    ret = SQLPrepare(adStmt,(unsigned char*)"INSERT INTO soakTable VALUES(1234,?,93333993,'CSQL_LAKSHYA');",SQL_NTS); 
    ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&rnd,0,NULL);
    ret = SQLBindParameter(adStmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&rnd,0,NULL);
    int i = 0;
    while (1) {
        if (ret == 0) { 
            timeout.tv_sec = 0;
            timeout.tv_usec = TS;
            os::select(0, 0, 0, 0, &timeout);
        }
        srand(time(0));
        if (i == 0) rnd = rand() % 16645635;
        else if (i == 1) rnd = (rand() / 17) % 16645635;
        else if (i == 2) rnd = (rand() / 19) % 16645635;
        else if (i == 3) rnd = (rand() / 23) % 16645635;
        else if (i == 4) { i = 0; rnd = (rand() / 29) % 16645635; }
        i++;
        ret = SQLExecute(stmt);
        if (ret == SQL_ERROR) SQLTransact(env, dbc, SQL_ROLLBACK);
        else ret = SQLTransact(env,dbc,SQL_COMMIT);
        ret = SQLExecute(adStmt);
        if (ret == SQL_ERROR) SQLTransact(env, adDbc, SQL_ROLLBACK);
        else ret = SQLTransact(env,adDbc,SQL_COMMIT);
        os::gettimeofday(&timeStamp);
        struct tm *tempTm = os::localtime(&timeStamp.tv_sec);
        strftime(msgBuf, 25, "%d/%m/%Y %H:%M:%S", tempTm);
        fprintf(fp, "Inserted PK: %8d %s\n", rnd, msgBuf);
        fflush(fp);
    }
    ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
    ret = SQLDisconnect(dbc);
    ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
    ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
    return 0;
}
