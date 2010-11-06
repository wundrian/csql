// Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
// CREATE TABLE "T1" WITH 10 FIELDS.
//  INSERT SOME TUPLES IN IT. 
//  DELETE TUPLES WITH WHERE CLAUSE.

//  Author : Jitendra Lenka
 
#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
    
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
      // STRUCTURE FIOR DATE DATATYPE
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
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER FOR ALL THE FIELD

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_SMALLINT,0,0,&f2,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3,0,&slen);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&f5,0,NULL);
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
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int DeleteTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "jitendra";
      float f4 = 2.5;
      float f5 = 10.50;
      
      int  f9 = 5;
      long long f10 = 15000;
      int result;
    
      SQLINTEGER slen=SQL_NTS;
    
      char strDate[20];
      char strTime[20];
      char strTimestamp[30];

      SQL_DATE_STRUCT date;
     

      date.year=2008;
      date.month=03;
      date.day=18;
      
      //**********************************************
      SQL_TIME_STRUCT time;
      time.hour = 5;
      time.minute = 22;
      time.second = 10;
      //*********************************************
      SQL_TIMESTAMP_STRUCT timestamp;
      timestamp.year = 2008;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576;
      
       int f1temp,f2temp;
       char f3temp[20];
       float f4temp, f5temp;
       SQL_DATE_STRUCT  f6Date;
       SQL_TIME_STRUCT  f7Time;
       SQL_TIMESTAMP_STRUCT  f8Timestamp;
       int f9temp;
       long long f10temp;
       
       ret = SQLPrepare(stmt,(unsigned char*)"DELETE  FROM T1 WHERE F1=? AND F2=? AND F3=? AND F4=? AND F5=? AND F6=? AND F7=? AND F8=? AND F9=? AND F10=?",SQL_NTS);
     checkrc(ret,__LINE__);

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
    ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1temp,0,NULL);
    checkrc(ret,__LINE__);
    
    ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_INTEGER,0,0,&f2temp,0,NULL);
    checkrc(ret,__LINE__);
    
    ret =  SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3temp,0,&slen);
    checkrc(ret,__LINE__);
    
    ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4temp,0,NULL);
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&f5temp,0,NULL);
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,6,SQL_PARAM_INPUT,SQL_C_TYPE_DATE,SQL_TYPE_DATE,196,0,&f6Date,sizeof(f6Date),&slen);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,7,SQL_PARAM_INPUT,SQL_C_TYPE_TIME,SQL_TYPE_TIME,196,0,&f7Time,sizeof(f7Time),&slen); 
    checkrc(ret,__LINE__);
   
    ret = SQLBindParameter(stmt,8,SQL_PARAM_INPUT,SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP,196,0,&f8Timestamp,sizeof(f8Timestamp),&slen);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,9,SQL_PARAM_INPUT,SQL_C_TINYINT,SQL_TINYINT,0,0,&f9temp,0,NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindParameter(stmt,10,SQL_PARAM_INPUT,SQL_C_SBIGINT,SQL_BIGINT,0,0,&f10temp,0,NULL);
    checkrc(ret,__LINE__);
    //*******************************************************************************************************

    int j, count=0;
   
    
    
    f6Date=date;
    f7Time=time;
    f8Timestamp=timestamp;
    for(j=0;j<20;j++)
    {
      f1temp=f1++;
      f2temp=f2++;
      strcpy(f3temp,"jitendra");
      f4temp=f4++;
      f5temp=f5;
      f9temp=f9;
      f10temp=f10;
      
      ret = SQLExecute(stmt);
      checkrc(ret,__LINE__);
      count++;
   }
        
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    
    printf("Total row deleted=%d\n",count);
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
                   (SQLCHAR *) "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;"),
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
        printf("error in connection\n");
        
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__); 
        return 1; 
    }

   
   //******************************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT)";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("\nTABLE CREATED\n"); 
   //*****************************
   InsertTest(env,dbc,stmt);  
   DeleteTest(env,dbc,stmt);

   //****************************************************************      
    SQLCHAR drop[100]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
       printf("Statement failed\n");
    else
       printf("Table  'T1' dropped successfully\n");  

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
