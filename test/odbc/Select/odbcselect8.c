// call SQLExecute() without calling SQLPrepare().
// it should fail.

// AUTHOR : Jitendra Lenka

#include<stdio.h>
#include<sql.h>
#include<stdlib.h>
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

//*************************************************************************
 
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
     "CREATE TABLE T1(F1 INT,F2 INT)";
  // ret = SQLPrepare(stmt,table,SQL_NTS);
//   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   int rettype = ret;
   if(ret)
   printf("Table creation failed\n");
   
   else
   printf("\nTABLE CREATED\n"); 
   //****************************************************************
   
   
   //****************************************************************      
   ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   
   if(rettype == 0)return 1;

   return 0;
 }        
