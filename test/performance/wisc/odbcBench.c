
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
bool mysql;

NanoTimer timer;
long long int timevalues[30]={0};
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


inline void checkrc (int rc, int line)
{
  if (rc)
    {
      cout << "Error " << rc << " at line: " << line << endl;
      exit (1);
    }
}

void readWriteTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_WRITE, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

void readOnlyTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_ONLY, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

void createHashIndex(SQLHANDLE hstmt,bool flag)
{
    int rc;
  if (mysql) {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx1 USING HASH ON big1(unique1);", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx2 USING HASH ON big2(unique1);", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx3 USING HASH ON small(unique1)", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx4 USING HASH ON big1(stringu1)", SQL_NTS );
    checkrc (rc, __LINE__);
  } else {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx1 ON big1(unique1) HASH;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx2 ON big2(unique1) HASH;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx3 ON small(unique1) HASH", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx4 ON big1(stringu1) HASH", SQL_NTS );
    checkrc (rc, __LINE__);
  }
}
void createTreeIndex(SQLHANDLE hstmt,bool flag)
{
    int rc;
    if (mysql)
    {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx5 USING BTREE ON big1(unique1);", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx6 USING BTREE ON big2(unique1);", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx7 USING BTREE ON small(unique1);", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx8 USING BTREE ON big1(stringu1);", SQL_NTS );
    checkrc (rc, __LINE__);
    }else {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx5 ON big1(unique1) TREE;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx6 ON big2(unique1) TREE;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx7 ON small(unique1) TREE;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE INDEX idx8 ON big1(stringu1) TREE;", SQL_NTS );
    checkrc (rc, __LINE__);
    }
   
}
void dropHashIndex(SQLHANDLE hstmt,bool flag)
{
    int rc;
    if (mysql) {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx1 on big1 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx2 on big2;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx3 on small", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx4 on big1;", SQL_NTS );
    checkrc (rc, __LINE__);
    } else {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx1 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx2 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx3 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx4 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    }
}
void dropTreeIndex(SQLHANDLE hstmt,bool flag)
{
    int rc;
    if (mysql)
    {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx5 on big1 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx6 on big2;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx7 on small;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx8 on big1;", SQL_NTS );
    checkrc (rc, __LINE__);
    }else {
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx5 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx6 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx7 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP INDEX idx8 ;", SQL_NTS );
    checkrc (rc, __LINE__);
    }

}

long long int onePerSel(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
   int uni1;
   int uni2;
   char str1[200];
   char str2[200];
   int val[] = {1, 5, 10, 50, 100, 500, 1000, 5000 ,7500, 9900};;
   int tempTermVar=0;
   int tempTermVar2=0;
   char tempval[124]="Value";
   int rc;
   readOnlyTrans (hdbc);
   rc = SQLPrepare (hstmt, (unsigned char *) "SELECT unique1, unique2, stringu1 from big1 where unique1 between ? and ?;", SQL_NTS);
   checkrc (rc, __LINE__);
   rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
   checkrc (rc, __LINE__);
   rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar2, 0, NULL);
   checkrc (rc, __LINE__);

   rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &uni1, 0, NULL);
   checkrc (rc, __LINE__);
   rc = SQLBindCol (hstmt, 2, SQL_INTEGER, &uni2, 0, NULL);
   checkrc (rc, __LINE__);
   rc = SQLBindCol (hstmt, 3, SQL_C_CHAR, str1, sizeof (str1), NULL);
   checkrc (rc, __LINE__);
   //rc = SQLBindCol (hstmt, 4, SQL_C_CHAR, str2, sizeof (str2), NULL);
   //checkrc (rc, __LINE__);
 
   int i, j, k;
   int Count;

   timer.reset ();

   /* Run 1per Test */
   for (i = 0; i < 10; i++)
   {
       Count=0;
       strcpy(tempval,"Value");
       tempTermVar = val[i] ;
       tempTermVar2 = val[i]+99 ;
       timer.start ();
       rc = SQLExecute (hstmt);
       checkrc (rc, __LINE__);
       while(SQL_SUCCEEDED(rc = SQLFetch(hstmt)))
       {
           Count++;
       }
   //    printf("Count=%d\n",Count);
       rc = SQLCloseCursor (hstmt);
       checkrc (rc, __LINE__);
       rc = SQLTransact (henv, hdbc, SQL_COMMIT);
       checkrc (rc, __LINE__);
       timer.stop ();
   }
   readWriteTrans (hdbc);
   //printf ("Read: 1 %lld\n", timer.avg ());
   return timer.avg()/1000;
}

long long int runReadTest (SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt,bool flag)
{
  int uni1;
  int uni2;
  char str1[200];
  char str2[200];

  int val[] = {1, 5, 10, 50, 100, 500, 1000, 5000 ,7500, 9999};;
  int tempTermVar=0;
  char tempval[124]="Value";
  int rc;

  /* Set read-only transaction type */
  readOnlyTrans (hdbc);
  if(flag){
  rc = SQLPrepare (hstmt, (unsigned char *) "SELECT unique1, unique2, stringu1, stringu2 from big1 where unique1=?;", SQL_NTS);
  }
  else  {
  rc = SQLPrepare (hstmt, (unsigned char *) "SELECT unique1, unique2, stringu1, stringu2 from big1 where stringu1=?;", SQL_NTS);
  }
  checkrc (rc, __LINE__);
  long sz = 0;
  if(flag){
      rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
      checkrc (rc, __LINE__);
  }
  else{
      rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_C_CHAR, 196, 0, tempval, 0, NULL);
      checkrc (rc, __LINE__);
  
  }
  rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &uni1, 0, NULL);
  checkrc (rc, __LINE__);
  rc = SQLBindCol (hstmt, 2, SQL_INTEGER, &uni2, 0, NULL);
  checkrc (rc, __LINE__);
  rc = SQLBindCol (hstmt, 3, SQL_C_CHAR, str1, sizeof (str1), NULL);
  checkrc (rc, __LINE__);
  rc = SQLBindCol (hstmt, 4, SQL_C_CHAR, str2, sizeof (str2), NULL);
  checkrc (rc, __LINE__);

  int i, j, k;
  int Count;

  timer.reset ();

  /* Run 1per Test */
  for (i = 0; i < 10; i++)
    {
          strcpy(tempval,"Value");
          if(flag){
	      tempTermVar = val[i] ;}
          else{
              char buf[10];
              sprintf(buf,"%d",val[i]);
              strcat(tempval,buf);
          }
	  timer.start ();
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLFetch (hstmt);
	  checkrc (rc, __LINE__);
          Count++;
	  rc = SQLCloseCursor (hstmt);
	  checkrc (rc, __LINE__);
	  rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	  checkrc (rc, __LINE__);
	  timer.stop ();
    }
  //printf ("Read: 1 %lld\n", timer.avg ());
  /* Set read-write transaction type */
  readWriteTrans (hdbc);
  return timer.avg()/1000;
}


//aggregate
long long int aggregate(SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt,bool flag)
{
    int summin;
    int rc;
     /* Set read-only transaction type */
    readOnlyTrans (hdbc);
    if(flag){
        rc = SQLPrepare (hstmt, (unsigned char *) "SELECT MIN(unique1) from big1;", SQL_NTS);
    }
    else  {
        rc = SQLPrepare (hstmt, (unsigned char *) "SELECT SUM(unique1) from big1;", SQL_NTS);
    }
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &summin, 0, NULL);
    checkrc (rc, __LINE__);

    int i, j, k;
    int Count;

    timer.reset ();
    for (i = 0; i < 10; i++)
    {
          timer.start ();
          rc = SQLExecute (hstmt);
          checkrc (rc, __LINE__);
          rc = SQLFetch (hstmt);
          checkrc (rc, __LINE__);
          Count++;
         // printf("value=%d",summin);
          rc = SQLCloseCursor (hstmt);
          checkrc (rc, __LINE__);
          rc = SQLTransact (henv, hdbc, SQL_COMMIT);
          checkrc (rc, __LINE__);
          timer.stop ();
    }
    //printf ("Read: 1 %lld\n", timer.avg ());
    /* Set read-write transaction type */
    readWriteTrans (hdbc);
    return timer.avg()/1000;
    
}

long long int dmlstatement(SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt,int val)
{
    int tempTermVar=10000,tempTermVar2=10000;
    int rc;
     /* Set read-only transaction type */
    readOnlyTrans (hdbc);
    if(val==1){
        rc = SQLPrepare (hstmt, (unsigned char *) "insert into big1 values(?,?,0,2,0,10,50,688,1950,4950,9950,1,100,'MXXXXXXXXXXXXXXXXXXXXXXXXXGXXXXXXXXXXXXXXXXXXXXXXXXC','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO');", SQL_NTS);
    }
    else  if(val==2){
        rc = SQLPrepare (hstmt, (unsigned char *) "UPDATE big1 SET two=1 WHERE unique1=?;", SQL_NTS);
    }else
    {
        rc = SQLPrepare (hstmt, (unsigned char *) "DELETE FROM big1 WHERE unique1=?;", SQL_NTS);
    }
    checkrc (rc, __LINE__);
    
    int i, j, k;
    int Count;

    timer.reset ();
    for (i = 0; i < 100; i++)
    {   tempTermVar+=i;
        rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
        checkrc (rc, __LINE__);
        if(val==1)
        {
           tempTermVar2+=i;
           rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar2, 0, NULL);
           checkrc (rc, __LINE__);
        }
        timer.start ();
        rc = SQLExecute (hstmt);
        checkrc (rc, __LINE__);
        rc = SQLTransact (henv, hdbc, SQL_COMMIT);
        checkrc (rc, __LINE__);
        timer.stop ();
        tempTermVar=10000;tempTermVar2=10000;
    }
    //printf ("Read: 1 %lld\n", timer.avg ());
    /* Set read-write transaction type */
    readWriteTrans (hdbc);
    return timer.avg()/1000;

}

//Joining
long long int joining(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt,int flag)
{
    int uni1;
    int uni2,uni3,uni4,uni5;
    char str1[200];
    char str2[200];

    int val[] = {1, 5, 10, 50, 100, 250, 500, 750, 900, 999};
    int tempTermVar=0;
    char tempval[124]="Value";
    int rc;

  /* Set read-only transaction type */
    readOnlyTrans (hdbc);
    if(flag==1){
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM small,big1 WHERE big1.unique1=small.unique1 AND small.unique1=?;", SQL_NTS);
    }
    else  {
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE small.unique1=big1.unique1 AND big1.unique1=big2.unique1 AND big1.unique1 = ?;", SQL_NTS);
    }
    checkrc (rc, __LINE__);
    long sz = 0;
    rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &uni1, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 2, SQL_INTEGER, &uni2, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 2, SQL_INTEGER, &uni3, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 4, SQL_C_CHAR, str1, sizeof (str1), NULL);
    checkrc (rc, __LINE__);
    if(flag==2){
        rc = SQLBindCol (hstmt, 5, SQL_INTEGER, &uni4, 0, NULL);
        checkrc (rc, __LINE__);
        rc = SQLBindCol (hstmt, 6, SQL_INTEGER, &uni5, 0, NULL);
        checkrc (rc, __LINE__);
    }
  int i, j, k;
  int Count;

  timer.reset ();

  /* Run 1per Test */
   for (i = 0; i < 10; i++)
    {
          tempTermVar = val[i] ;
          timer.start ();
          rc = SQLExecute (hstmt);
          checkrc (rc, __LINE__);
          rc = SQLFetch(hstmt);
          Count++;
//          printf("%d,%d\n",uni1,uni3);
          rc = SQLCloseCursor (hstmt);
          checkrc (rc, __LINE__);
          rc = SQLTransact (henv, hdbc, SQL_COMMIT);
          checkrc (rc, __LINE__);
          timer.stop ();
    }
  //printf ("Read: 1 %lld\n", timer.avg ());
   /* Set read-write transaction type */
    readWriteTrans (hdbc);
    return timer.avg()/1000;
}


void printTime()
{
    printf("Wisconsin Benchmark Report:\n");
    printf("*******************************************************\n");
    printf(" Statement               \t NoIndex Hash\t Tree\n");
    printf("*******************************************************\n");
    printf(" SelectInt 1               \t %lld\t %lld \t %lld\n",timevalues[0],timevalues[1],timevalues[2]);
    printf(" SelectStr 1               \t %lld\t %lld \t %lld\n",timevalues[3],timevalues[4],timevalues[5]);
    printf(" 1Per Sel                    \t %lld\t %lld \t %lld\n\n",timevalues[6],timevalues[7],timevalues[8]);
    printf(" Min All                    \t %lld\t %lld \t %lld\n",timevalues[9],timevalues[10],timevalues[11]);
    printf(" Sum All                    \t %lld\t %lld \t %lld\n\n",timevalues[12],timevalues[13],timevalues[14]);
    printf(" Insert 1                    \t %lld\t %lld \t %lld\n",timevalues[15],timevalues[16],timevalues[17]);
    printf(" Update 1                    \t %lld\t %lld \t %lld\n",timevalues[18],timevalues[19],timevalues[20]);
    printf(" Delete 1                    \t %lld\t %lld \t %lld\n\n",timevalues[21],timevalues[22],timevalues[23]);
    printf(" Join(10K*1K)1          \t %lld\t %lld \t %lld\n",timevalues[24],timevalues[25],timevalues[26]);
    printf(" Join(10K*10K*1K)1         \t %lld\t %lld \t %lld\n",timevalues[27],timevalues[28],timevalues[29]);
    printf("*******************************************************\n");
    
}

int main (int ac, char **av)
{
  int rc;
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  mysql=false;
  if (ac ==2) mysql = true;
  //printf("Mysql Set %d \n", ac); return 0;
  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
  checkrc (rc, __LINE__);
  if (!mysql) {
      rc = SQLConnect (hdbc,
		   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
		   (SQLCHAR *) "root",
		   (SQLSMALLINT) strlen ("root"),
		   (SQLCHAR *) "manager",
		   (SQLSMALLINT) strlen (""));
  }else {

      SQLCHAR outstr[1024];
      SQLSMALLINT outstrlen;
      rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)"DSN=myodbc3;", SQL_NTS,
                         outstr, sizeof(outstr), &outstrlen,
                         SQL_DRIVER_NOPROMPT);
  }

 
  if (SQL_SUCCEEDED(rc)) {
    printf("Connected\n");
    //printf("Returned connection string was:\n\t%s\n", outstr);
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }

  //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  checkrc (rc, __LINE__);
  int ins=1,upd=2,del=3;
//Query 1
  timevalues[0] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[3] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[6] = onePerSel(henv, hdbc, hstmt);
  timevalues[9] = aggregate(henv, hdbc, hstmt,true);
  timevalues[12] = aggregate(henv, hdbc, hstmt,false);
  timevalues[15] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[18] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[21] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[24] = joining(henv, hdbc, hstmt,1);
  timevalues[27] = joining(henv, hdbc, hstmt,2);
  printf("NON INDEX OVER\n");

//Hash
  createHashIndex( hstmt,true);
  timevalues[1] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[4] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[7] = onePerSel(henv, hdbc, hstmt);
  timevalues[10] = aggregate(henv, hdbc, hstmt,true);
  timevalues[13] = aggregate(henv, hdbc, hstmt,false);
  timevalues[16] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[19] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[22] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[25] = joining(henv, hdbc, hstmt,1);
  timevalues[28] = joining(henv, hdbc, hstmt,2);
  dropHashIndex(hstmt,true);
  printf("HASH INDEX OVER\n");
  //printTime();

//TREE
  createTreeIndex(hstmt,true);
  timevalues[2] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[5] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[8] = onePerSel(henv, hdbc, hstmt);
  timevalues[11] = aggregate(henv, hdbc, hstmt,true);
  timevalues[14] = aggregate(henv, hdbc, hstmt,false);
  timevalues[17] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[20] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[23] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[26] = joining(henv, hdbc,hstmt,1);
  timevalues[29] = joining(henv, hdbc,hstmt,2);
  dropTreeIndex(hstmt,true);
  printf("TREE INDEX OVER\n");

  printTime();
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



