// create table T1 with 10 fields.insert some record.
// update some fields with where clause(f2=?)

// Author :  Jitendra Lenka 


#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>

inline void checkrc(int rc,int line) 
{
  if(rc)
  {
     printf("ERROR %d at line %d\n",rc,line);
     exit(1);

  }
}

int InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
    int ret;
    int f1=90;
    short int f2=20;
    char f3[20]="jitendra";
    float f4=2.5;
    float f5=10.50;
    int f9=5;
    long long f10=15000;
    int result;
 
    SQLINTEGER slen = SQL_NTS;
    
    SQL_DATE_STRUCT date;
    date.year=2008;
    date.month=03;
    date.day=18;

    SQL_TIME_STRUCT time;
    time.hour = 5;
    time.minute = 22;
    time.second =10;

    SQL_TIMESTAMP_STRUCT timestamp;
    timestamp.year = 2008;
    timestamp.month = 03;
    timestamp.day = 18;
    
    timestamp.hour = 5;
    timestamp.minute =22;
    timestamp.second = 10;
    timestamp.fraction = 764576;

    ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?)",SQL_NTS);
    checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_SMALLINT,0,0,&f2,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3,0,&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f5,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,6,SQL_PARAM_INPUT,SQL_C_TYPE_DATE,SQL_TYPE_DATE,196,0,&date,sizeof(date),&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,7,SQL_PARAM_INPUT,SQL_C_TYPE_TIME,SQL_TYPE_TIME,196,0,&time,sizeof(time),&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,8,SQL_PARAM_INPUT,SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP,196,0,&timestamp,sizeof(timestamp),&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,9,SQL_PARAM_INPUT,SQL_C_TINYINT,SQL_TINYINT,0,0,&f9,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,10,SQL_PARAM_INPUT,SQL_C_SBIGINT,SQL_BIGINT,0,0,&f10,0,NULL);
   checkrc(ret,__LINE__);

   int count=0,i;
   for(i=0;i<10;i++)
   {
     f1++;
     f2++;
     ret = SQLExecute(stmt);
     checkrc(ret,__LINE__);

     ret = SQLTransact(env,dbc,SQL_COMMIT);
     checkrc(ret,__LINE__);

     count++;
   }

   printf("%d Rows Inserted\n",count);
}

//*******************************************************************
int UpdateTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
   SQLRETURN ret;
   SQLINTEGER slen;
   short int f2temp;
   char f3temp[30];
   float f4temp;
   float f5temp;
   long long f10temp;
   SQL_DATE_STRUCT f6Date;
   SQL_TIMESTAMP_STRUCT f8Timestamp;
   
   
   
     
   ret = SQLPrepare(stmt,(unsigned char*)"UPDATE T1 SET F10=? ,F8=?,F6=?,F5=?,F4=?,F3=? WHERE F2=? ",SQL_NTS);
   checkrc(ret,__LINE__);

   SQLSMALLINT nop;
   SQLNumParams(stmt,&nop);
   printf("Number of parameters=%d\n",nop);

   ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SBIGINT,SQL_BIGINT,0,0,&f10temp,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP,196,0,&f8Timestamp,sizeof(f8Timestamp),&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_TYPE_DATE,SQL_TYPE_DATE,196,0,&f6Date,sizeof(f6Date),&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&f5temp,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4temp,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,6,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3temp,0,&slen);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,7,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_INTEGER,0,0,&f2temp,0,NULL);
   checkrc(ret,__LINE__);
   //**************************************************************************************************
   
  f2temp=20;int count1=0;
  for(int i=0;i<5;i++)
  {
   f2temp++;
   strcpy(f3temp,"Lakshya");
   f4temp=9.5;
   f5temp=15.90;
   
   f6Date.year=2009;
   f6Date.month=12;
   f6Date.day=31;

   f8Timestamp.year=2009;
   f8Timestamp.month=12;
   f8Timestamp.day=31;
   f8Timestamp.hour=9;
   f8Timestamp.minute=35;
   f8Timestamp.second=55;
   f8Timestamp.fraction=1234;
   f10temp=12000;

   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   ret = SQLTransact(env,dbc,SQL_COMMIT);
   checkrc(ret,__LINE__);
   count1++;
  }
  printf("%d Rows updated\n",count1); 
   
} 
int FetchTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
	SQLRETURN ret;
	long long int f10=12000;

        SQL_TIMESTAMP_STRUCT timestamp;
	timestamp.year = 2007;
	timestamp.month = 3;
	timestamp.day = 15;

        timestamp.hour = 12;
	timestamp.minute = 15;
	timestamp.second = 30;

        SQL_DATE_STRUCT date;
        date.year = 2007;
	date.month = 3;
	date.day = 10;

        float f5=2.4;
        float f4=10.3;
        char f3[10]="LAKSHYA";

	ret = SQLPrepare(stmt,(unsigned char*)"SELECT F10,F8,F6,F5,F4,F3 FROM T1",SQL_NTS);
        checkrc(ret,__LINE__);

	ret = SQLBindCol(stmt,1,SQL_C_SBIGINT,&f10,0,NULL);
	checkrc(ret,__LINE__);

	ret = SQLBindCol(stmt,2,SQL_C_TYPE_TIMESTAMP,&timestamp,sizeof(timestamp),NULL);
	checkrc(ret,__LINE__);
 
	ret = SQLBindCol(stmt,3,SQL_C_TYPE_DATE,&date,sizeof(date),NULL);
        checkrc(ret,__LINE__);
        
	ret = SQLBindCol(stmt,4,SQL_C_FLOAT,&f5,0,NULL);
	checkrc(ret,__LINE__);

	ret = SQLBindCol(stmt,5,SQL_C_FLOAT,&f4,0,NULL);
	checkrc(ret,__LINE__);

	ret = SQLBindCol(stmt,6,SQL_C_CHAR,f3,sizeof(f3),NULL);
	checkrc(ret,__LINE__);

	int count=0;
	ret = SQLExecute(stmt);
	checkrc(ret,__LINE__);
        printf("Fetching starts on table 't1'\n");
	while(SQL_SUCCEEDED(ret=SQLFetch(stmt)))
	{
	   
           printf("F10=%lld\tTIMESTAMP=%d-%d-%d %d:%d:%d\tDATE=%d-%d-%d\tF5=%f\tF4=%f\tF3=%s\n",f10,timestamp.year,timestamp.month,timestamp.day,timestamp.hour,timestamp.minute,timestamp.second,date.year,date.month,date.day,f5,f4,f3);
           count++;
	}

	ret = SQLCloseCursor(stmt);
	checkrc(ret,__LINE__);

	ret = SQLTransact(env,dbc,SQL_COMMIT);
	checkrc(ret,__LINE__);

	printf("Total row fetched=%d\n",count);
}
     
	


int main()
{
   SQLHENV  env;
   SQLHDBC  dbc;
   SQLHSTMT stmt;
   SQLRETURN ret;
   SQLCHAR outstr[1024];
   SQLSMALLINT outstrlen;
   
   ret = SQLAllocHandle(SQL_HANDLE_ENV , SQL_NULL_HANDLE,&env);
   checkrc(ret,__LINE__);

   SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void *)SQL_OV_ODBC3,0);
   
   ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
   checkrc(ret,__LINE__);

    ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

   checkrc(ret,__LINE__);
  
   if(SQL_SUCCEEDED(ret))
   {
       printf("\nConnected to the datastring\n");
       
   }

   else
   {
       printf("error in connection\n");
       
       ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
       checkrc(ret,__LINE__); 

       ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
       checkrc(ret,__LINE__);
       return 1; 
   }  

   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);

   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT)";

   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);

   printf("Table 'T1' created\n");
   //**********************************
   InsertTest(env,dbc,stmt);
   UpdateTest(env,dbc,stmt);
   FetchTest(env,dbc,stmt);
    //*********************************
   SQLCHAR drop[30]="DROP TABLE T1";
   
   ret = SQLPrepare(stmt,drop,SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);

   if(ret!=SQL_SUCCESS && ret!=SQL_SUCCESS_WITH_INFO)
     printf("Statement failed\n");
   else
     printf("Table 'T1' Dropped successfully\n");
 
   

   ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);

   return 0;
} 
    
 
