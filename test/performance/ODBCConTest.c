/*  This program has two different aspect
 *  1.  Use ($./ODBCConTest conn) command to get the timer result
 *      which starts from Connection and goes through pprepare, execute, commit
 *      and ends at Disconnect for each iteration.
 *  
 *  2.  Use ($./ODBCConTest prepare) command to get the timer result 
 *  
 *      which starts at prepare and ends after commit for each iteration.
 *
 * Author: Jitendra Lenka
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sql.h>
#include <sqlext.h>
#include "NanoTimer.h"
#define ITERATION 100
using namespace std;
#define DSN "test"
//#define DSN "DSN=mycsql;MODE=CSQL;SERVER=192.168.1.103;PORT=5678;""DSN=mycsql;MODE=CSQL;SERVER=192.168.1.103;PORT=5678;"

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

int
runInsertTest (SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  
    int rc,i;
    int iHolder;
    char sHolder[200];
    char sData[200];

   timer.reset();
   for(i=0;i<ITERATION;i++){
    timer.start();
   
    rc = SQLConnect (hdbc,
                    (SQLCHAR *) DSN, SQL_NTS,
                    (SQLCHAR *) "root",
                    (SQLSMALLINT) strlen ("root"),
                    (SQLCHAR *) "manager",
                    (SQLSMALLINT) strlen (""));
   
     if (SQL_SUCCEEDED(rc)) {
        if (rc == SQL_SUCCESS_WITH_INFO) {
           printf("Driver reported the following diagnostics\n");
           extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
        }
     }else {
          fprintf(stderr, "Failed to connect\n");
          extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
     }
     
      //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
      checkrc (rc, __LINE__);
      
      rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
      checkrc (rc, __LINE__);
      rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
      checkrc (rc, __LINE__);

  iHolder = 0;
  strcpy (sData, "0123456789012345678901234567890123456789");
  rc = SQLPrepare (hstmt, (unsigned char *) "INSERT INTO t1 VALUES (?, ?)",
		   SQL_NTS);
  checkrc (rc, __LINE__);
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  SQLINTEGER sLen = SQL_NTS;
  rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
			 196, 0, (void *) sHolder, 0, &sLen);
  checkrc (rc, __LINE__);
  int tCount;

	  iHolder = i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  //timer.stop ();

	  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLDisconnect (hdbc);
	  checkrc (rc, __LINE__);
	  timer.stop();
      }
      printf ("Insert: %lld  %lld  %lld\n", timer.min(), timer.max(),timer.avg());
      return 0;
}
//From prepare to Commit (Inserting)
int InsertTest(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
	
    int rc,i;
    int iHolder;
    char sHolder[200];
    char sData[200];

  iHolder = 0;
  strcpy (sData, "0123456789012345678901234567890123456789");
  timer.reset();
  for(i=0;i<ITERATION;i++){
  timer.start();
  rc = SQLPrepare (hstmt, (unsigned char *) "INSERT INTO t1 VALUES (?, ?)",
		   SQL_NTS);
  checkrc (rc, __LINE__);
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  SQLINTEGER sLen = SQL_NTS;
  rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
			 196, 0, (void *) sHolder, 0, &sLen);
  checkrc (rc, __LINE__);
  int tCount;

	  iHolder = i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();

      }
      printf("Insert: %lld  %lld  %lld\n", timer.min(), timer.max(),timer.avg());
      return 0;
}

//From Prepare to commit (Read)
int ReadTest(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
    int iHolder;
    char sHolder[200];
    char sData[200];
      
    int tempTermVar = 0;
    int tempTermVal = 0;
    int rc,i;

  // Set read-only transaction type 
  readOnlyTrans (hdbc);
  timer.reset();
  for(i=0;i<ITERATION;i++){
  timer.start();
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

  int tCount;

	  tempTermVar = i ;
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLFetch (hstmt);
	  checkrc (rc, __LINE__);
	  tempTermVal = iHolder;
	  strcpy (sData, sHolder);
	  rc = SQLCloseCursor (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop();
  
   }
   printf("Select: %lld  %lld  %lld\n", timer.min(), timer.max(),timer.avg());
   readWriteTrans (hdbc);
   return rc;


}

int
runReadTest (SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  
    int iHolder;
    char sHolder[200];
    char sData[200];
      
    int tempTermVar = 0;
    int tempTermVal = 0;
    int rc,i;

  timer.reset(); 
  for(i=0;i<ITERATION;i++){
  timer.start();
   
     rc = SQLConnect (hdbc,
                     (SQLCHAR *) DSN, SQL_NTS,
                     (SQLCHAR *) "root",
                     (SQLSMALLINT) strlen ("root"),
                     (SQLCHAR *) "manager",
                     (SQLSMALLINT) strlen (""));
   
     if (SQL_SUCCEEDED(rc)) {
        if (rc == SQL_SUCCESS_WITH_INFO) {
          printf("Driver reported the following diagnostics\n");
          extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
        }
     }else {
           fprintf(stderr, "Failed to connect\n");
           extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
      }
    
       //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
       checkrc (rc, __LINE__);
       rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
       checkrc (rc, __LINE__);
       rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
       checkrc (rc, __LINE__);

  // Set read-only transaction type 
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

  int tCount;

	  tempTermVar = i ;
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLFetch (hstmt);
	  checkrc (rc, __LINE__);
	  tempTermVal = iHolder;
	  strcpy (sData, sHolder);
	  rc = SQLCloseCursor (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  
	  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLDisconnect (hdbc);
	  checkrc (rc, __LINE__);
	  timer.stop();
  
   }
   printf("Select: %lld  %lld  %lld\n", timer.min(), timer.max(),timer.avg());
   return rc;

}

//From Prepare to Commit(Update
int UpdateTest(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
		
  int rc,i;
  int iHolder;
  char sHolder[200];
  char sData[200];

  timer.reset();
  for(i=0;i<ITERATION;i++){
  timer.start();
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

	  iHolder = i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
     }
     printf ("Update: %lld  %lld  %lld\n", timer.min (), timer.max (),timer.avg ());
}

int
runUpdateTest (SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  int rc,i;
  int iHolder;
  char sHolder[200];
  char sData[200];

  timer.reset();
  for(i=0;i<ITERATION;i++){
  timer.start();
   
     rc = SQLConnect (hdbc,
                     (SQLCHAR *) DSN, SQL_NTS,
                     (SQLCHAR *) "root",
                     (SQLSMALLINT) strlen ("root"),
                     (SQLCHAR *) "manager",
                     (SQLSMALLINT) strlen (""));
   
     if (SQL_SUCCEEDED(rc)) {
        if (rc == SQL_SUCCESS_WITH_INFO) {
          printf("Driver reported the following diagnostics\n");
          extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
        }
     }else {
           fprintf(stderr, "Failed to connect\n");
           extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
      }  
       checkrc (rc, __LINE__);
       rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
       checkrc (rc, __LINE__);
       rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  
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

  int tCount;

	  iHolder = i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  
	  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLDisconnect (hdbc);
	  checkrc (rc, __LINE__);
	  timer.stop ();
     }
     printf ("Update: %lld  %lld  %lld\n", timer.min (), timer.max (),timer.avg ());
     return 0;
}

//From prepare to commit(Delete)
int DeleteTest(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  int rc,i;
  int iHolder;
       timer.reset();
       for(i=0;i<ITERATION;i++){
       timer.start();
       rc = SQLPrepare (hstmt, (unsigned char *)"DELETE FROM t1 WHERE f1 = ?", SQL_NTS);
       checkrc (rc, __LINE__);
       rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
       checkrc (rc, __LINE__);
       
       iHolder = 0;
       int tCount;
  
	  iHolder = i ;
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);

	  timer.stop ();
  }
  printf ("Delete: %lld  %lld  %lld\n", timer.min (), timer.max (),timer.avg ());
  return 0;
}


int
runDeleteTest (SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  int rc,i;
  int iHolder;
  
  timer.reset();
  for(i=0;i<ITERATION;i++){
    timer.start();
   
     rc = SQLConnect (hdbc,
                     (SQLCHAR *) DSN, SQL_NTS,
                     (SQLCHAR *) "root",
                     (SQLSMALLINT) strlen ("root"),
                     (SQLCHAR *) "manager",
                     (SQLSMALLINT) strlen (""));
   
     if (SQL_SUCCEEDED(rc)) {
        if (rc == SQL_SUCCESS_WITH_INFO) {
          printf("Driver reported the following diagnostics\n");
          extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
        }
     }else {
           fprintf(stderr, "Failed to connect\n");
           extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
      }
    
       //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
       checkrc (rc, __LINE__);
       rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
       checkrc (rc, __LINE__);

       rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
       checkrc (rc, __LINE__);

  
       rc = SQLPrepare (hstmt, (unsigned char *)"DELETE FROM t1 WHERE f1 = ?", SQL_NTS);
       checkrc (rc, __LINE__);
       rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
       checkrc (rc, __LINE__);
       
       iHolder = 0;
       int tCount;
  
	  iHolder = i ;
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);

	  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLDisconnect (hdbc);
	  checkrc (rc, __LINE__);

	  timer.stop ();
  }
  printf ("Delete: %lld  %lld  %lld\n", timer.min (), timer.max (),timer.avg ());
  return 0;

}

int
main (int ac, char *av[])
{
   int flag=1;
  
   	if(ac==2){
	if(strcmp(av[1],"conn")==0)flag=1;
	else if(strcmp(av[1],"prepare")==0)flag=2;
        else
	{
		printf("\nValid value: conn or prepare\n");
		return 1;
	}
   }
	   
   SQLRETURN rc; 
   SQLHENV henv;
   SQLHDBC hdbc;
   SQLHSTMT hstmt;

   rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
   checkrc (rc, __LINE__);
   SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

   rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
   checkrc (rc, __LINE__);
  
   rc = SQLConnect (hdbc,
		   (SQLCHAR *) DSN, SQL_NTS,
		   (SQLCHAR *) "root",
		   (SQLSMALLINT) strlen ("root"),
		   (SQLCHAR *) "manager",
		   (SQLSMALLINT) strlen (""));
 
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    if (SQL_SUCCEEDED(rc)) {
     //  printf("Connected\n");
       if (rc == SQL_SUCCESS_WITH_INFO) {
          printf("Driver reported the following diagnostics\n");
          extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
       } 
    }else {
             fprintf(stderr, "Failed to connect\n");
             extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
    }

  //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  checkrc (rc, __LINE__);
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE TABLE t1 (f1 INTEGER, f2 char(196), primary key (f1));", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("Table 't1' Created\n");


  //Disconnect from the data source
      
  printf("-----------------------------------\n");
  printf("Stmt: |   Min   |   Max  |  Avg\n");
  printf("-----------------------------------\n");
  
if(flag==1)
{
     rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
     checkrc (rc, __LINE__);
     rc = SQLDisconnect (hdbc);
     checkrc (rc, __LINE__);
    
     runInsertTest (henv, hdbc, hstmt);
     runReadTest (henv, hdbc, hstmt);
     runUpdateTest (henv, hdbc, hstmt);
     runDeleteTest (henv, hdbc, hstmt);
     // Again connect

      rc = SQLConnect (hdbc,
                      (SQLCHAR *) DSN, SQL_NTS,
                      (SQLCHAR *) "root",
                      (SQLSMALLINT) strlen ("root"),
                      (SQLCHAR *) "manager",
                      (SQLSMALLINT) strlen (""));
   
     if (SQL_SUCCEEDED(rc)) {
     // printf("Connected\n");
      if (rc == SQL_SUCCESS_WITH_INFO) {
        printf("Driver reported the following diagnostics\n");
        extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
       }
     }else {
       fprintf(stderr, "Failed to connect\n");
        extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
     }
  
    check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
    checkrc (rc, __LINE__);
    rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
    checkrc (rc, __LINE__);
    rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  
}
if(flag==2)
{
     
    InsertTest (henv, hdbc, hstmt);
    ReadTest (henv, hdbc, hstmt);
    UpdateTest (henv, hdbc, hstmt);
    DeleteTest (henv, hdbc, hstmt);
    
}

  printf("----------------------------------\n");
  printf("                    |Unit: NanoSec|\n");
  //For dropping table

  rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP TABLE t1;", SQL_NTS );
  checkrc (rc, __LINE__);
  printf("Table 't1' Dropped\n");
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
