//       connect to the DATA SOURCE with the connection string
//	 DSN=mycsql;MODE=INVALID MODE;SERVER=localhost;PORT=5678;
//       disconnect from the data source. It Should be Failed

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
    
  // connect to the DSN data source
  ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=INVALID;SERVER=localhost;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=INVALID;SERVER=localhost;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen ("manager"));
//SERVER=192.168.1.114;PORT=5678

  if(SQL_SUCCEEDED(ret))
  {
     printf("\nTest Failed..\n");
     ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
     checkrc(ret,__LINE__);
  
     ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
     checkrc(ret,__LINE__);
     return 2;
  }

   printf("Test Passed..\n"); 
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   return 0;
}         
