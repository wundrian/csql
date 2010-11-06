/*  CREATE TABLE "T1" WITH 10 FIELDS.
    CREATE TABLE "T2" WITH 10 FIELDS.
    CREATE TABLE "T3" WITH 10 FIELDS.
    SQLTables()  Should return all table information
    CatalogName="csql", SchemaName="csql", TableType="table"
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

int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
      int ret;
      char f1[50]= "praba";
      char f2[50]= "praba";
      char f3[50]= "praba";
      char f4[50]= "praba";
      char f5[50]= "praba";

     ret = SQLTables(stmt,(SQLCHAR*)"Csql", SQL_NTS, (SQLCHAR*)"Csql", SQL_NTS, NULL, SQL_NTS, (SQLCHAR*)"table", SQL_NTS );
//     ret = SQLTables(stmt, (SQLCHAR*)"Csql", NULL,(SQLCHAR*)"cSQL", NULL, NULL, NULL, (SQLCHAR*)"view", NULL );
     checkrc(ret,__LINE__);
    short totalFields=0;
    ret = SQLNumResultCols (stmt, &totalFields); 
    checkrc(ret,__LINE__);
    printf( "No of columns in resultset = %d\n",totalFields);

    ret = SQLBindCol(stmt,1,SQL_C_CHAR,f1,sizeof(f1),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,2,SQL_C_CHAR,f2,sizeof(f2),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f3,sizeof(f3),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,4,SQL_C_CHAR,f4,sizeof(f4),NULL);
    checkrc(ret,__LINE__);
    ret = SQLBindCol(stmt,5,SQL_C_CHAR,f5,sizeof(f5),NULL);
    checkrc(ret,__LINE__);
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
       printf("\tF1=%s \t F2=%s \t F3=%s \t F4= %s \t F5=%s \n ",f1,f2,f3,f4,f5);
  }
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
       checkrc(ret,__LINE__);
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

// ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=myodbc3", SQL_NTS, outstr, sizeof(outstr), &outstrlen,SQL_DRIVER_NOPROMPT);

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
   ret = SQLPrepare(stmt,(SQLCHAR*)"create table t2 (f1 int,primary key(f1));",SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   ret = SQLPrepare(stmt,(SQLCHAR*)"create table t3 (f1 int);",SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);

   printf("\nTABLE CREATED\n"); 
   //***************************
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

    ret = SQLPrepare(stmt,(SQLCHAR*)"drop table t2",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    {   
      printf("Statement failed\n");
       return 2;
    }
     

    ret = SQLPrepare(stmt,(SQLCHAR*)"drop table t3",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    {   
      printf("Statement failed\n");
       return 2;
    }
       printf("Tables  dropped successfully\n");  

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
