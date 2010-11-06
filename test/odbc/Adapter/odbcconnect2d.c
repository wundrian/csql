//    sqlconnect,sqldisconnect and then again call sqlconnect.it should pass.
//    connect to the DATA SOURCE with the connection string "DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;"
//    see retrieving ODBC Diagnostics

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
  //**************************************************************************************************  
  // connect to the DSN mydsn
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

  
  if(SQL_SUCCEEDED(ret))
  {
     printf("\nConnected to the Data Source successfully..\n");
          
  }
   else
   {
        printf("connection failed\n");
        
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__);
        
        return 1;
   }

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   printf("Disconnected from the Datasource\n");
   //**************************************************************************************************
   // again sqlconnect 
   
   
    
   
   ret =   SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));

   int rettype =ret;
    
  if(SQL_SUCCEEDED(ret))
  {
     printf("Again Connected to the Data Source successfully..\n");
     

  }
   else
   {
        printf("connection failed\n");
        
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__);

        return 1;
   }

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
 
   //**************************************************************************************************
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   if(rettype !=0)return 1;
   return 0;
}         
