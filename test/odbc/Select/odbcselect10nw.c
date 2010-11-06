//Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
//CREATE TABLE "T1" WITH 10 FIELDS.
//  INSERT SOME TUPLES IN IT. AND FETCH ALL THE TUPLES.
//  BindCol show bind with char type
//  Author: jitendra Lenka


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
      int f1=50; // f1 field
      short int f2=0;//f2 field
      char f3[50]= "Praba";
      float f4 = 2.5;
      float f5 = 10.50;
      int  f9 = 5;
      long long f10 = 15000;
      int result;

      SQLINTEGER slen = SQL_NTS;
      //***********************************
      // STRUCTURE FIOR DATE DATATYPE
      SQL_DATE_STRUCT date;
      
      
      date.year=2007;
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
      timestamp.year = 2007;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
       
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
      for(i=0;i<10;i++)
      {
         f1++;
         f2++;
         f4++;
        // date.month = date.month+1;
         date.day = date.day+1; 
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
         date.month = date.month+1;
                 
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }
//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      char f1[10][50] = { "jitendra"};
      int result;


      SQL_DATE_STRUCT date;
      char strDate[30];

      date.year=2007;
      date.month=03;
      date.day=18;
     // strcpy(strDate,"{d '2008-03-18'}");
      //**********************************************
      SQL_TIME_STRUCT time;
      time.hour = 5;
      time.minute = 22;
      time.second = 10;
      //*********************************************
      SQL_TIMESTAMP_STRUCT timestamp;
      timestamp.year = 2007;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
      

     ret = SQLPrepare(stmt,(unsigned char*)"SELECT * FROM T1",SQL_NTS);
     checkrc(ret,__LINE__);

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
    ret = SQLBindCol(stmt,1,SQL_C_CHAR, f1[0],sizeof(f1[0]),NULL);
    checkrc(ret,__LINE__);
    
    ret = SQLBindCol(stmt,2,SQL_C_CHAR, f1[1],sizeof(f1[1]),NULL);
    checkrc(ret,__LINE__);


    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f1[2],sizeof(f1[2]),NULL);
    checkrc(ret,__LINE__);
 
    ret = SQLBindCol(stmt,4,SQL_C_CHAR,f1[3],sizeof(f1[3]),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,5,SQL_C_CHAR,f1[4],sizeof(f1[4]),NULL);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,6,SQL_C_CHAR,f1[5],sizeof(f1[5]),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,7,SQL_C_CHAR,f1[6],sizeof(f1[6]),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,8,SQL_C_CHAR,f1[7],sizeof(f1[7]),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,9,SQL_C_CHAR,f1[8],sizeof(f1[8]),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,10,SQL_C_CHAR,f1[9],sizeof(f1[9]),NULL);
    checkrc(ret,__LINE__);
/*
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
*/
    int j, count=0;
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    printf("Fetching starts on table  T1 :\n");
    
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("F1=%s\tF2=%s\tF3=%s\tF4=%s\tF5=%s\tDATE=%s\tTIME=%s\tTIMESTAMP=%s\tF9=%s\tF10=%s\n ",f1[0],f1[1],f1[2],f1[3],f1[4],f1[5],f1[6],f1[7],f1[8],f1[9]);
        count++;
           
    }
    
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);
    
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
  ret =  SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
  checkrc(ret,__LINE__); 
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
     printf("\nConnected to the Data Source SUCCESSFULLY..\n");
     
 
  }
   else
   {
        printf("error in connection\n");                
        return 1;
 
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
   FetchTest(env,dbc,stmt);

   //****************************************************************      
    SQLCHAR drop[100]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    {   
     printf("Statement failed\n");
     return 2;
    }
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
