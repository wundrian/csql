/*  CREATE TABLE "T1" WITH 10 FIELDS.
    SQLDescribeParam() should return Should return all field defination 
    SQLNumParams() should return no of parameter in the prepare statement
*/

#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
#include<CSql.h>    
//*************************************************************************
// ERROR CHECK FUNCTION
inline void checkrc(int rc,int line)
{
   if(rc)
   {
       printf("ERROR %d at line %d\n",rc,line);
       exit(1);
   }
}

//*************************************************************************
// FUNCTION FOR INSERTING ROWS IN IT.

int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      int ret;
      int f1=90; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "jitendra";
      float f4 = 2.5;
      float f5 = 10.50;
      int  f9 = 5;
      long long f10 = 15000;
      int result;

      SQLINTEGER slen = SQL_NTS;
      //***********************************
      // STRUCTURE FOR DATE DATATYPE
      SQL_DATE_STRUCT date;
      char strDate[30];
      
      date.year=2008;
      date.month=03;
      date.day=18;
     // strcpy(strDate,"{d '2008-03-18'}");  
      //*******************************
      //  STRUCTURE FOR TIME DATATYPE.
      SQL_TIME_STRUCT time;
      time.hour = 5;
      time.minute = 22;
      time.second = 10;
      //*****************************
      // STRUCTURE FOR TIMESTAMP DATATYPE
      SQL_TIMESTAMP_STRUCT timestamp;
      timestamp.year = 2008;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576; 
     //******************************
      // PREPARE THE STATEMENT.
      
      
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?);",SQL_NTS);
      checkrc(ret,__LINE__);
      
      // BIND PARAMETER FOR ALL THE FIELD
       short totalFields=0;
      ret = SQLNumParams (stmt, &totalFields);
      checkrc(ret,__LINE__);
      printf("No of parameter %d\n", totalFields);
      UWORD                   icol;
    UCHAR                   colName[IDENTIFIER_LENGTH];
    SWORD                   colNameMax;
    SWORD                   nameLength;
    SWORD                   colType;
    SQLULEN                 colLength;
    SWORD                   scale;
    SWORD                   nullable;
    icol = 1; colNameMax = IDENTIFIER_LENGTH;
  while (icol <= totalFields)
    {
        ret = SQLDescribeParam(stmt, icol, &colType, &colLength,&scale, &nullable);
        checkrc(ret,__LINE__);
        printf("Param Type %d , length %d,Scale %d Nullinfo %d\n",colType,colLength,scale,nullable);
        icol++;
    } 


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

      int i,count=0;
      // EXECUTE THE STATEMENT
      for(i=0;i<20;i++)
      {
         f1++;
         f2++;
         f4++;
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
        
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }
//***********************************************************************
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
      int ret;
      int f1=10; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "praba";
      float f4 = 2.5;
      float f5 = 10.50;
      int f9=5;
      long long f10=15000;
      SQLINTEGER slen = SQL_NTS;
      SQL_DATE_STRUCT  date,f6Date;
      SQL_TIME_STRUCT  time, f7Time;
      SQL_TIMESTAMP_STRUCT  timestamp, f8Timestamp;

      date.year=2008;
      date.month=03;
      date.day=18;

      time.hour=5;
      time.minute=22;
      time.second=10;

      timestamp.year=2008;
      timestamp.month=03;
      timestamp.day=18;
      timestamp.hour=5;
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576;

       int f1temp,f2temp;
       char f3temp[20];
       float f4temp, f5temp;

       int f9temp;
       long long f10temp;

     ret = SQLPrepare(stmt,(unsigned char*)"SELECT *  FROM T1 ",SQL_NTS);
     checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,2,SQL_C_SSHORT,&f2,0,NULL);
    checkrc(ret,__LINE__);


    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f3,sizeof(f3),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,4,SQL_C_FLOAT,&f4,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,5,SQL_C_FLOAT,&f5,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,6,SQL_C_TYPE_DATE,&date,sizeof(date),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,7,SQL_C_TYPE_TIME,&time,sizeof(time),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,8,SQL_C_TYPE_TIMESTAMP,&timestamp,sizeof(timestamp),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,9,SQL_C_TINYINT,&f9,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,10,SQL_C_SBIGINT,&f10,0,NULL);
    checkrc(ret,__LINE__);

    int j, count=0;



    f6Date=date;
    f7Time=time;
    f8Timestamp=timestamp;
    for(j=0;j<10;j++)
    {
      f1temp=f1++;
      f2temp=f2++;
      strcpy(f3temp,"praba");
      f4temp=f4++;
      f5temp=f5;
      f9temp=f9;
      f10temp=f10;

      ret = SQLExecute(stmt);
      checkrc(ret,__LINE__);
      ret = SQLFetch(stmt);
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);
      count++;

       printf("F1=%d\tF2=%d\tF3=%s\tF4=%f\tF5=%f\tDATE=%d/%d/%d\tTIME=%d-%d-%d\tTIMESTAMP=%d/%d/%d %d-%d-%d\tF9=%d\tF10=%lld\n ",f1,f2,f3,f4,f5,date.year,date.month,date.day,time.hour,time.minute,time.second,timestamp.year,timestamp.month,timestamp.day,timestamp.hour,timestamp.minute,timestamp.second,f9,f10);


  }

    ret = SQLTransact(env,dbc,SQL_COMMIT);
       checkrc(ret,__LINE__);

    printf("Total row fetched=%d\n",count);
    return 0;
}

 
 
int main()
{
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret;
  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  
  // Aloocate an environment handle
  ret=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
  checkrc(ret,__LINE__);
  
   //we need odbc3 support
   SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
   
  //ALLOCATE A Connection handle
  ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
  checkrc(ret,__LINE__);
    
  // connect to the DSN mydsn
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));


  if(SQL_SUCCEEDED(ret))
  {
     printf("\nConnected to the Data Source..\n");
     
   
     
  }
   else
   {
        printf("error in conenction\n");
     
         ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
         checkrc(ret,__LINE__);

         ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
         checkrc(ret,__LINE__);
         return 1;
   }

   
   //*****************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT);";
   
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("\nTABLE CREATED\n"); 
   //***************************
   InsertTest(env,dbc,stmt);  
   FetchTest(env,dbc,stmt);
   //**************************************************      
    SQLCHAR drop[100]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    {   
      printf("Statement failed\n");
       return 1;
    }
    else
       printf("Table 'T1' dropped successfully\n");  

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
