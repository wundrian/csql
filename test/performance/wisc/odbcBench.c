
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
long long int timevalues[30][3]={0};
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
   char str1[52];
   char str2[52];
   int val[] = {1, 5, 10, 50, 100, 500, 1000, 5000 ,7500, 9500};
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
 
   int i, j, k;
   int Count;

   timer.reset ();

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
       if (Count != 100) {
           printf("One % Selection returned %d rows", Count);
           readWriteTrans (hdbc);
           return 0;
       }
   }
   readWriteTrans (hdbc);
   //printf ("Read: 1 %lld\n", timer.avg ());
   return timer.avg()/1000;
}

long long int runReadTest (SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt,bool flag)
{
  int uni1;
  int uni2;
  char str1[52];
  char str2[52];

  int val[] = {1, 10, 100, 500, 1000, 5000 ,7500, 8000, 9000, 9999};
  int tempTermVar=0;
  char tempval[52]="Value";
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
  char buf[10]="Value";

  /* Run 1per Test */
  for (i = 0; i < 10; i++)
    {
          if(flag){
	      tempTermVar = val[i] ;}
          else{
              sprintf(tempval,"%s%d",buf, val[i]);
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

//DISTINCT
long long int distinct(SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt)
{
    int var_onepercent;
    int rc;
    
    readOnlyTrans (hdbc);
    rc = SQLPrepare (hstmt, (unsigned char *) "SELECT DISTINCT onepercent FROM big1;", SQL_NTS);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &var_onepercent, 0, NULL); 
    checkrc (rc, __LINE__);

    int i,count;
    timer.reset ();

    for (i = 0; i < 10; i++)
    {
        count=0;
        timer.start ();
	rc = SQLExecute (hstmt);
	checkrc (rc, __LINE__);
	while(SQL_SUCCEEDED(rc = SQLFetch(hstmt))){
            count++;
        }
	//checkrc (rc, __LINE__);
	rc = SQLCloseCursor (hstmt);
	checkrc (rc, __LINE__);
	rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	checkrc (rc, __LINE__);
	timer.stop ();
        if (count != 100) {
            printf("distinct returned %d rows\n");
            readWriteTrans(hdbc);
            return 0;
        }
    }
    readWriteTrans(hdbc);
    return timer.avg()/1000;
}
long long int orderBy(SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt)
{
    int val[] = {1, 5, 10, 50, 100, 500, 1000, 5000 ,7500, 9500};
    int var_two, var_four, var_ten, var_twenty, var_onepercent;
    char str1[52];
    int tempTermVar=0, tempTermVar2=0, tempTermVar3=0;
    int rc;
    
    rc = SQLPrepare (hstmt, (unsigned char *) "SELECT two, four, ten, twenty, onepercent, string4 from big1 where unique1 between ? and ? order by unique1;", SQL_NTS);
    checkrc (rc, __LINE__);

    readOnlyTrans (hdbc);
    rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar2, 0, NULL);
    checkrc (rc, __LINE__);


    rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &var_two, 0, NULL);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 2, SQL_INTEGER, &var_four, 0, NULL);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 3, SQL_INTEGER, &var_ten, 0, NULL);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 4, SQL_INTEGER, &var_twenty, 0, NULL);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 5, SQL_INTEGER, &var_onepercent, 0, NULL);
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 6, SQL_C_CHAR, str1, sizeof (str1), NULL);
    checkrc (rc, __LINE__);

    
    int i, j, k;
    int count;

    timer.reset ();

    for (i = 0; i < 10; i++)
    {
       count=0;
       tempTermVar=val[i];
       tempTermVar2 = val[i]+100 ;
       timer.start ();
       rc = SQLExecute (hstmt);
       checkrc (rc, __LINE__);
       rc = SQLFetch (hstmt);
       while(SQL_SUCCEEDED(rc = SQLFetch(hstmt))) count++;
       //checkrc (rc, __LINE__);
       rc = SQLCloseCursor (hstmt);
       checkrc (rc, __LINE__);
       rc = SQLTransact (henv, hdbc, SQL_COMMIT);
       checkrc (rc, __LINE__);
       timer.stop ();
       if (count != 100) {
           printf("orderby returned %d rows \n", count);
           readWriteTrans(hdbc);
           return 0;
       }
   }
   readWriteTrans(hdbc);
   return timer.avg()/1000;
}


//aggregate
long long int aggregate(SQLHANDLE henv, SQLHANDLE hdbc,SQLHANDLE hstmt,int val,bool flag)
{
    int summinmax=0,tempTermVar=0;
    int rc;
     /* Set read-only transaction type */
    readOnlyTrans (hdbc);
    if(val==1 && flag){
        rc = SQLPrepare (hstmt, (unsigned char *) "SELECT MIN(unique1) from big1;", SQL_NTS);
    }
    else if(val==1 && !flag)
    {
       rc = SQLPrepare (hstmt, (unsigned char *) "SELECT MIN(unique1) from big1 group by onepercent;", SQL_NTS);

    }
    else if(val==2 && flag) {
       rc = SQLPrepare (hstmt, (unsigned char *) "SELECT MAX(unique1) from big1;", SQL_NTS);
    }
    else if(val==2 && !flag){
       rc = SQLPrepare (hstmt, (unsigned char *) "SELECT MAX(unique1) from big1 group by onepercent;", SQL_NTS);
    }
    else if(val==3 && flag) {
       rc = SQLPrepare (hstmt, (unsigned char *) "SELECT SUM(unique1) from big1;", SQL_NTS);
    }
    else if(val==3 && !flag){
       rc = SQLPrepare (hstmt, (unsigned char *) "SELECT SUM(unique1) from big1 group by onepercent;", SQL_NTS);
    }
    checkrc (rc, __LINE__);

    rc = SQLBindCol (hstmt, 1, SQL_INTEGER, &summinmax, 0, NULL);
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
long long int joining(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt,int value)
{
    int uni1;
    int uni2,uni3,uni4,uni5;
    char str1[52];
    char str2[52];

    int val[10] = {1, 5, 10, 50, 100, 250, 500, 750, 900, 999};
    int tempTermVar=0;
    char tempval[124]="Value";
    int rc;

  /* Set read-only transaction type */
    readOnlyTrans (hdbc);
    if(value==1 ){
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM big1,small WHERE big1.unique1=small.unique1 AND big1.unique1=?;", SQL_NTS);
    }
    
    else {
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE small.unique1=big1.unique2 AND big1.unique2=big2.unique1 AND big1.unique1 = ?;", SQL_NTS);
    }

    checkrc (rc, __LINE__);
    long sz = 0;
    
    
    rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar, 0, NULL);
    checkrc (rc, __LINE__);
    
    rc = SQLBindCol (hstmt, 1, SQL_C_LONG, &uni1, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 2, SQL_C_LONG, &uni2, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 3, SQL_C_LONG, &uni3, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 4, SQL_C_CHAR, str1, sizeof (str1), NULL);
    checkrc (rc, __LINE__);
    if(value==2 ){
        rc = SQLBindCol (hstmt, 5, SQL_C_LONG, &uni4, 0, NULL);
        checkrc (rc, __LINE__);
        rc = SQLBindCol (hstmt, 6, SQL_C_LONG, &uni5, 0, NULL);
        checkrc (rc, __LINE__);
    }
    int i, j, k;
    int Count=0;

    timer.reset ();

    for (i = 0; i < 10; i++)
    {
        tempTermVar = val[i];
        timer.start ();
        rc = SQLExecute (hstmt);
        checkrc (rc, __LINE__);
        rc=SQLFetch(hstmt);
        Count++;
        rc = SQLCloseCursor (hstmt);
        checkrc (rc, __LINE__);
        rc = SQLTransact (henv, hdbc, SQL_COMMIT);
        checkrc (rc, __LINE__);
        timer.stop ();
        // printf("uni1=%d uni2=%d uni3=%d str1=%s \n",uni1,uni2,uni3,str1);
    }
    readWriteTrans (hdbc);
    return timer.avg()/1000;
}
//JOINCondition

long long int joinCondition(SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt,int value)
{
    int uni1;
    int uni2,uni3,uni4,uni5;
    char str1[52];
    char str2[52];
    int rc;
    int searchVal[] = {1, 5, 10, 50, 100, 200, 250, 500, 750, 800};

  //Set read-only transaction type 
    readOnlyTrans (hdbc);
    if(value==1 )
    {
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT big1.unique1, big1.unique2, small.unique1, small.stringu1 FROM big1,small WHERE big1.unique1=small.unique1 AND big1.unique1 > ? and big1.unique1 <= ?;", SQL_NTS);

    }
    else {
      rc = SQLPrepare (hstmt, (unsigned char *) "SELECT small.unique1, big1.unique1, big2.unique1, small.stringu1, big1.unique2, big2.unique2 FROM big1, big2, small WHERE big1.unique1=small.unique1 AND big1.unique1=big2.unique1 AND big1.unique1 > ? and big1.unique1 <= ?;", SQL_NTS);
    }

    checkrc (rc, __LINE__);
    int tempTermVar1 =0, tempTermVar2=0;

    rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar1, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempTermVar2, 0, NULL);
    checkrc (rc, __LINE__);

    long sz = 0;
    rc = SQLBindCol (hstmt, 1, SQL_C_SLONG, &uni1, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 2, SQL_C_SLONG, &uni2, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 3, SQL_C_SLONG, &uni3, 0, NULL);
    checkrc (rc, __LINE__);
    rc = SQLBindCol (hstmt, 4, SQL_C_CHAR, str1, sizeof (str1), NULL);
    checkrc (rc, __LINE__);
    if(value==2){
        rc = SQLBindCol (hstmt, 5, SQL_C_SLONG, &uni4, 0, NULL);
        checkrc (rc, __LINE__);
        rc = SQLBindCol (hstmt, 6, SQL_C_SLONG, &uni5, 0, NULL);
        checkrc (rc, __LINE__);
    }
  int i, j, k;
  int count=0;

  timer.reset ();
  for(i=0;i<10;i++){
    count=0;
    tempTermVar1 = searchVal[i];
    tempTermVar2 = searchVal[i]+100;
    timer.start ();
    rc = SQLExecute (hstmt);
    checkrc (rc, __LINE__);
    while(SQL_SUCCEEDED(rc = SQLFetch(hstmt)))
    {
      count++;
      //printf("Uni1:%d uni2=%d uni3=%d \n",uni1,uni2,uni3);
    }
    rc = SQLCloseCursor (hstmt);
    checkrc (rc, __LINE__);
    rc = SQLTransact (henv, hdbc, SQL_COMMIT);
    checkrc (rc, __LINE__);
    timer.stop ();
    if (count != 100) {
       printf ("range join returned %d rows\n", count);
       readWriteTrans (hdbc);
       return 0;
    }
  }
  readWriteTrans (hdbc);
  return timer.avg()/1000;

}

void printTime()
{
    printf("Wisconsin Benchmark Report:\n");
    printf("*******************************************************\n");
    printf(" Statement               \tNoIndex\tHash\tTree\n");
    printf("*******************************************************\n");
    printf(" SelectInt 1		\t%lld\t%lld\t%lld\n",timevalues[0][0],timevalues[0][1],timevalues[0][2]);
    printf(" SelectStr 1		\t%lld\t%lld\t%lld\n",timevalues[1][0],timevalues[1][1],timevalues[1][2]);
    printf(" 1Per Sel		\t%lld\t%lld\t%lld\n",timevalues[2][0],timevalues[2][1],timevalues[2][2]);
    printf(" Min All		\t%lld\t%lld\t%lld\n",timevalues[3][0],timevalues[3][1],timevalues[3][2]);
    printf(" Min GrBy 1%		\t%lld\t%lld\t%lld\n",timevalues[4][0],timevalues[4][1],timevalues[4][2]);
    printf(" Max All		\t%lld\t%lld\t%lld\n",timevalues[5][0],timevalues[5][1],timevalues[5][2]);
    printf(" Max GrBy 1		\t%lld\t%lld\t%lld\n",timevalues[6][0],timevalues[6][1],timevalues[6][2]);
    printf(" Sum All		\t%lld\t%lld\t%lld\n",timevalues[7][0],timevalues[7][1],timevalues[7][2]);
    printf(" Sum GrBy 1%		\t%lld\t%lld\t%lld\n",timevalues[8][0],timevalues[8][1],timevalues[8][2]);
    printf(" Distinct 1%		\t%lld\t%lld\t%lld\n",timevalues[9][0],timevalues[9][1],timevalues[9][2]);
    printf(" Order By 1%		\t%lld\t%lld\t%lld\n",timevalues[10][0],timevalues[10][1],timevalues[10][2]);
    printf(" Insert 1		\t%lld\t%lld\t%lld\n",timevalues[11][0],timevalues[11][1],timevalues[11][2]);
    printf(" Update 1		\t%lld\t%lld\t%lld\n",timevalues[12][0],timevalues[12][1],timevalues[12][2]);
    printf(" Delete 1		\t%lld\t%lld\t%lld\n",timevalues[13][0],timevalues[13][1],timevalues[13][2]);
    printf(" Join(10K*1K)1		\t%lld\t%lld\t%lld\n",timevalues[14][0],timevalues[14][1],timevalues[14][2]);
    printf(" Join(10K*10K*1K)	\t%lld\t%lld\t%lld\n",timevalues[15][0],timevalues[15][1],timevalues[15][2]);
    printf(" Join(10K*1K)100	\t%lld\t%lld\t%lld\n",timevalues[16][0],timevalues[16][1],timevalues[16][2]);
    printf(" Join(10K*10K*1K)100	\t%lld\t%lld\t%lld\n",timevalues[17][0],timevalues[17][1],timevalues[17][2]);


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
  int min=1, max=2, sum=3;

  timevalues[0][0] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[1][0] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[2][0] = onePerSel(henv, hdbc, hstmt);
  timevalues[3][0] = aggregate(henv, hdbc, hstmt,min,true);
  timevalues[4][0] = aggregate(henv, hdbc, hstmt,min,false);
  timevalues[5][0] = aggregate(henv, hdbc, hstmt,max,true);
  timevalues[6][0] = aggregate(henv, hdbc, hstmt,max,false);
  timevalues[7][0] = aggregate(henv, hdbc, hstmt,sum,true);
  timevalues[8][0] = aggregate(henv, hdbc, hstmt,sum,false);
  timevalues[9][0] = distinct(henv, hdbc, hstmt);
  timevalues[10][0] = orderBy(henv, hdbc, hstmt);  
  timevalues[11][0] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[12][0] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[13][0] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[14][0] = joining(henv, hdbc, hstmt,1);
  timevalues[15][0] = joining(henv, hdbc, hstmt,2);
  timevalues[16][0] = joinCondition(henv, hdbc, hstmt,1);
  timevalues[17][0] = joinCondition(henv, hdbc, hstmt,2);
  printf("NON INDEX OVER\n");
  if (!mysql){
      rc = SQLExecDirect(hstmt, (SQLCHAR*) "FLUSH CACHE", SQL_NTS );
      checkrc (rc, __LINE__);
  }

//Hash
  createHashIndex( hstmt,true);

  timevalues[0][1] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[1][1] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[2][1] = onePerSel(henv, hdbc, hstmt);
  timevalues[3][1] = aggregate(henv, hdbc, hstmt,min,true);
  timevalues[4][1] = 0;
  timevalues[5][1] = 0;
  timevalues[6][1] = 0;
  timevalues[7][1] = 0;
  timevalues[8][1] = 0;
  timevalues[9][1] = distinct(henv, hdbc, hstmt);
  timevalues[10][1] = orderBy(henv, hdbc, hstmt);  
  timevalues[11][1] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[12][1] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[13][1] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[14][1] = joining(henv, hdbc, hstmt,1);
  timevalues[15][1] = joining(henv, hdbc, hstmt,2);

  timevalues[16][1] = joinCondition(henv, hdbc, hstmt,1);
  timevalues[17][1] = joinCondition(henv, hdbc, hstmt,2);
  dropHashIndex(hstmt,true);
  printf("HASH INDEX OVER\n");
  //printTime();
  
  
  if (!mysql){
      rc = SQLExecDirect(hstmt, (SQLCHAR*) "FLUSH CACHE", SQL_NTS );
      checkrc (rc, __LINE__);
  }


//TREE
  createTreeIndex(hstmt,true);
  timevalues[0][2] = runReadTest (henv, hdbc, hstmt,true);
  timevalues[1][2] = runReadTest (henv, hdbc, hstmt,false);
  timevalues[2][2] = onePerSel(henv, hdbc, hstmt);
  timevalues[3][2] = aggregate(henv, hdbc, hstmt,min,true);
  timevalues[4][2] = 0;
  timevalues[5][2] = 0;
  timevalues[6][2] = 0;
  timevalues[7][2] = 0;
  timevalues[8][2] = 0;
  timevalues[9][2] = distinct(henv, hdbc, hstmt);
  timevalues[10][2] = orderBy(henv, hdbc, hstmt);  
  timevalues[11][2] = dmlstatement(henv, hdbc, hstmt,ins); 
  timevalues[12][2] = dmlstatement(henv, hdbc, hstmt,upd);
  timevalues[13][2] = dmlstatement(henv, hdbc, hstmt,del);
  timevalues[14][2] = joining(henv, hdbc, hstmt,1);
  timevalues[15][2] = joining(henv, hdbc, hstmt,2);

  timevalues[16][2] = joinCondition(henv, hdbc, hstmt,1);
  timevalues[17][2] = joinCondition(henv, hdbc, hstmt,2);

  dropTreeIndex(hstmt,true);
  printf("TREE INDEX OVER\n");
  

  //printTime
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



