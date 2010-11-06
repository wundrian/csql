
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sql.h>
#include <sqlext.h>
#include "NanoTimer.h"
#define THREADS 5
#define ITERATION 1000
using namespace std;

#define DSN 

NanoTimer timer;

void extract_error(
    char *fn,
    SQLHANDLE handle,
    SQLSMALLINT type)
{
    SQLINTEGER	 i = 0;
    SQLINTEGER	 native;
    SQLCHAR	 state[ 7 ];
    SQLCHAR	 text[256];
    SQLSMALLINT	 len;
    SQLRETURN	 ret;

    fprintf(stderr,
            "\n"
            "The driver reported the following diagnostics whilst running "
            "%s\n\n",
            fn);

    do
    {
        ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
                            sizeof(text), &len );
        if (SQL_SUCCEEDED(ret))
            printf("%s:%ld:%ld:%s\n", state, i, native, text);
    }
    while( ret == SQL_SUCCESS );
}

inline void
check_error (SQLSMALLINT handleType, SQLHANDLE handle, int rc, int line)
{
  if (rc)
    {
      cout << "Error " << rc << " at line: " << line << endl;
      SQLCHAR state[10];
      SQLINTEGER native;
      SQLCHAR mesg[300];
      int i=0;
      while (SQLGetDiagRec (handleType, handle, i++, state, &native, mesg, 300,
			    NULL) == SQL_SUCCESS)
	{
	  mesg[299] = '\0';
	  cout << "state: " << state << endl;
	  cout << "native: " << native << endl;
	  cout << "mesg: " << mesg << endl;
	}
      exit (1);
    }
}


inline void
checkrc (int rc, int line)
{
  if (rc)
    {
      cout << "Error " << rc << " at line: " << line << endl;
      exit (1);
    }
}

void
readWriteTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_WRITE, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

void
readOnlyTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_ONLY, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

void *runInsertTest (void *massage)
{
  int thno;
  thno =*(int*)massage;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  int rc;
  int iHolder;
  char sHolder[200];
  char sData[200];
  char *dsn = (char *) "DSN=test;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
                   (SQLCHAR *) dsn, SQL_NTS,
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

   SQLCHAR outstr[1024];
   SQLSMALLINT outstrlen;
  if (SQL_SUCCEEDED(rc)) {
   // printf("Connected\n");
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect",hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  checkrc (rc, __LINE__);


  iHolder = 0;
  strcpy (sData, "0123456789012345678901234567890123456789");
  rc = SQLPrepare (hstmt, (unsigned char *) "INSERT INTO t1 VALUES (?, ?)",  SQL_NTS);
  

  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  SQLINTEGER sLen = SQL_NTS;
  rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
			 196, 0, (void *) sHolder, 0, &sLen);
  checkrc (rc, __LINE__);
  int i, j, k;
  int tCount;

  timer.reset ();
  int tryno=2;
  /* Run 1per Test */
  for (i = 0; i < ITERATION; i++)
    {
          tryno=2;
	  timer.start ();
	  iHolder = ITERATION*thno +i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
          while(rc!=0 && tryno!=0)
          {
             rc = SQLExecute (hstmt);
             tryno--;
          }
          if( 0==tryno ) { printf("BREAK IN INSERT THREAD NO %d\n",thno); break;}
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
    }
   
  printf("Thread No %d\t No Of Record Insert %d\n",thno,i);  
  rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);

  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);

  return NULL;

}

void * runReadTest (void *massage)
{
  int iHolder;
  char sHolder[200];
  char sData[200];
  int thno;
  thno =*(int*)massage;

  int tempTermVar = 0;
  int tempTermVal = 0;
  int rc;
  char *dsn;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  dsn = (char *) "DSN=test;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &(hdbc));
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
                   (SQLCHAR *) dsn, SQL_NTS,
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  if (SQL_SUCCEEDED(rc)) {
    //printf("Connected\n");
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect",hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &(hstmt));
  checkrc (rc, __LINE__);

  /* Set read-only transaction type */
  readOnlyTrans (hdbc);
  rc = SQLPrepare (hstmt, (unsigned char *)
		   "SELECT f1, f2 FROM t1 where f1 = ?", SQL_NTS);
  checkrc (rc, __LINE__);
  long sz = 0;
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &tempTermVar, 0, NULL);
  checkrc (rc, __LINE__);
  rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  rc = SQLBindCol (hstmt, 2, SQL_C_CHAR, sHolder, sizeof (sHolder), NULL);
  checkrc (rc, __LINE__);
  iHolder = 0;
  strcpy (sData, "0123456789012345678901234567890123456789");

  int i, j, k;
  int tCount;

  timer.reset ();
  int tryno=2;
  int count=0;
  /* Run 1per Test */
  for (i = 0; i < ITERATION; i++)
    {
	  timer.start ();
	  tempTermVar = ITERATION*thno +i ;
	  rc = SQLExecute (hstmt);
          while(rc!=0 && tryno!=0)
          {
            rc = SQLExecute (hstmt);
            tryno--; 
          }
          if(0==tryno) {printf("BREAK IN SELECT THREAD NO %d\n",thno); break;}
          if(SQL_SUCCEEDED(rc = SQLFetch(hstmt)))
          {
             count++;
          }
	  strcpy (sData, sHolder);
	  rc = SQLCloseCursor (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
    }
    printf("Thread No %d\t No Of Record Select %d\n",thno,count);
  /* Set read-write transaction type */
  rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);

  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);

  return NULL;
}

void *runUpdateTest (void *massage)
{
  int thno;
  thno =*(int*)massage;

  int rc;
  int iHolder;
  char sHolder[200];
  char sData[200];
  char *dsn;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  dsn = (char *) "DSN=test;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &(hdbc));
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
                   (SQLCHAR *) dsn, SQL_NTS,
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  if (SQL_SUCCEEDED(rc)) {
   // printf("Connected\n");
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect",hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &(hstmt));
  checkrc (rc, __LINE__);

  rc = SQLPrepare (hstmt,
		   (unsigned char *) "UPDATE t1 SET f2 = ? WHERE f1 = ?",
		   SQL_NTS);
  checkrc (rc, __LINE__);
  SQLINTEGER sLen = SQL_NTS;
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
			 196, 0, (void *) sHolder, 0, &sLen);
  checkrc (rc, __LINE__);
  rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  iHolder = 0;
  strcpy (sData, "9876543210987654321098765432109876543210");

  int i, j, k;
  int tCount;

  timer.reset ();
  int tryno=2;
  for (i = 0; i < ITERATION; i++)
    {
	  timer.start ();
	  iHolder = ITERATION*thno+1;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
          while(rc!=0 && tryno!=0)
          {
            rc = SQLExecute (hstmt);
            tryno--;
          }
          if(0==tryno) {printf("BREAK IN UPDATE THREAD NO %d\n",thno); break;}
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
    }
    printf("Thread No %d\t No Of Record Update %d\n",thno,i);
 rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);

  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);

  return NULL;
}

void *runDeleteTest (void *massage)
{
  int thno;
  thno =*(int*)massage;
  int rc;
  int iHolder;
  char *dsn;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  dsn = (char *) "DSN=test;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &(hdbc));
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
                   (SQLCHAR *) dsn, SQL_NTS,
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  if (SQL_SUCCEEDED(rc)) {
   // printf("Connected\n");
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect",hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &(hstmt));
  checkrc (rc, __LINE__);

  rc = SQLPrepare (hstmt, (unsigned char *)
		   "DELETE FROM t1 WHERE f1 = ?", SQL_NTS);
  checkrc (rc, __LINE__);
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  iHolder = 0;
  int i, j, k;
  int tCount;
  timer.reset ();
  int tryno=2;
  for (i = 0; i < ITERATION; i++)
    {
	  timer.start ();
	  iHolder = ITERATION*thno+i ;
	  rc = SQLExecute (hstmt);
          while(rc!=0 && tryno!=0)
          {
            rc = SQLExecute (hstmt);
            tryno--;
          }
          if(0==tryno) {printf("BREAK IN DELETE THREAD NO %d\n",thno); break;}
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
    }
    printf("Thread No %d\t No Of Record Delete %d\n",thno,i);
  //printf ("Delete: 1 %lld %lld %lld\n", timer.min (), timer.max (), timer.avg ());
  rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);

  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);

  return NULL;

}


int main (int ac, char **av)
{
  int rc;
  char *dsn;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  dsn = (char *) "DSN=test;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &(hdbc));
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
		   (SQLCHAR *) dsn, SQL_NTS,
		   (SQLCHAR *) "root",
		   (SQLSMALLINT) strlen ("root"),
		   (SQLCHAR *) "manager",
		   (SQLSMALLINT) strlen (""));
 
  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  if (SQL_SUCCEEDED(rc)) {
    //printf("Connected\n");
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect",hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &(hstmt));
  checkrc (rc, __LINE__);
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE TABLE t1 (f1 INTEGER, f2 char(196));", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("t1 Table Created\n");
#ifdef HASH
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx1 on t1(f1) hash;", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("Hash Index Created\n");
#endif
#ifdef TREE
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx1 on t1(f1) tree;", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("Tree Index Created\n");
#endif
  pthread_t thr[THREADS];
  int message[THREADS];
  int status;
  printf("Insert Operartion \n");
  for (int i=0; i <THREADS; i++) 
  {
        message[i] = i;
        pthread_create (&thr[i], NULL, &runInsertTest, (void *) &message[i]);
  }
  for (int i=0; i <THREADS; i++) {
       pthread_join(thr[i], (void**)&status);
  }
  printf("Select Operartion \n"); 
  for (int i=0; i <THREADS; i++)
  {
        message[i] = i;
        pthread_create (&thr[i], NULL, &runReadTest, (void *) &message[i]);
  }
  for (int i=0; i <THREADS; i++) {
       pthread_join(thr[i], (void**)&status);
  }
  printf("Update Operartion \n");  
  for (int i=0; i <THREADS; i++)
  {
        message[i] = i;
        pthread_create (&thr[i], NULL, &runUpdateTest, (void *) &message[i]);
  }
  for (int i=0; i <THREADS; i++) {
       pthread_join(thr[i], (void**)&status);
  }
  printf("Delete Operartion \n");
  for (int i=0; i <THREADS; i++)
  {
        message[i] = i;
        pthread_create (&thr[i], NULL, &runDeleteTest, (void *) &message[i]);
  }
  for (int i=0; i <THREADS; i++) {
       pthread_join(thr[i], (void**)&status);
  }

  rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP TABLE t1;", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("t1 Table Droped\n");
  rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);

  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);
  exit (0);
}
