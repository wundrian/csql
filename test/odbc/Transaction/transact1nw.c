//Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
//create table T1 with two integer field. perform insert,update,select.

// AUTHOR : Jitendra Lenka

#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
    
//*************************************************************************

inline void checkrc(int rc,int line)
{
   if(rc)
   {
       printf("ERROR %d at line %d\n",rc,line);
       exit(1);
   }
}


// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      SQLRETURN  ret;
      int f2=20;//f2 field



    ret = SQLPrepare(stmt,(unsigned char*)"SELECT F2  FROM T1 ",SQL_NTS);
    checkrc(ret,__LINE__);

    //ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SMALL,SQL_SMALL,0,0,)
    ret = SQLBindCol(stmt,1,SQL_C_LONG,&f2,0,NULL);
    checkrc(ret,__LINE__);
    
    int j, count=0;
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("F2=%d\n",f2);
        count++;
                
    }
    
    /*SQLSMALLINT noc;
    SQLNumResultCols(stmt,&noc);
    printf("SQLNumResultCols() returns=%d\n",noc);*/
    
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
   ret =SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
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

   ret = SQLSetConnectAttr(dbc,SQL_ATTR_AUTOCOMMIT,(void*)SQL_AUTOCOMMIT_OFF,SQL_IS_UINTEGER);
   checkrc(ret,__LINE__);
   //******************************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 INT);";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   SQLFreeStmt(stmt, SQL_CLOSE);
   
   printf("\nTABLE CREATED\n"); 
   //****************************************************************
    ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(1,1);",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    
    SQLFreeStmt(stmt, SQL_CLOSE);
    ret = SQLEndTran(SQL_HANDLE_DBC,dbc,SQL_COMMIT);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    printf("error in commit\n");
   //InsertTest(env,dbc,stmt);  
   //*****************************************************************
    
    //update
    ret = SQLPrepare(stmt,(unsigned char*)"UPDATE T1 SET F2=100;",SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    SQLFreeStmt(stmt, SQL_CLOSE);
    ret = SQLEndTran(SQL_HANDLE_DBC,dbc,SQL_COMMIT);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    printf("error in commit\n");
    checkrc(ret,__LINE__);
   //***********************************************************
     //FETCH
    FetchTest(env,dbc,stmt);

   //****************************************************************      
   ret = SQLExecDirect(stmt,(unsigned char*)"DROP TABLE T1",SQL_NTS);
   checkrc(ret,__LINE__);
   SQLFreeStmt(stmt, SQL_CLOSE);
   printf("Table T1 dropped\n");

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
