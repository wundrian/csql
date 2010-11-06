//Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
//select from non-existing table it should fail

//  AUTHOR : Jitendra lenka

#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>

inline  void checkrc(int rc, int line)
{
   if(rc)
   {
      printf("ERROR %d at line %d\n",rc,line);
      exit(1);
   }
}
//**********************************************************************************

int main()
{
   SQLHENV  env;
   SQLHDBC  dbc;
   SQLHSTMT stmt;
   SQLRETURN ret;
   SQLCHAR outstr[1024];
   SQLSMALLINT  outstrlen;

   ret = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
   checkrc(ret,__LINE__);

   ret = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
   checkrc(ret,__LINE__);

   ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
   checkrc(ret,__LINE__);

   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));
 
  if(SQL_SUCCEEDED(ret))
   {
       printf("Connected to the data source successfully..\n");

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

     ret = SQLPrepare(stmt,(unsigned char*)"SELECT * FROM EMP",SQL_NTS);
     
     
     ret = SQLExecute(stmt);

     if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
     printf("Could not SQL Execute\n");
     int rettype = ret;
     


     ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
     checkrc(ret,__LINE__);

     ret = SQLDisconnect(dbc);
     checkrc(ret,__LINE__);

     ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
     checkrc(ret,__LINE__);

     ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
     checkrc(ret,__LINE__); 
     if(rettype == 0) 
     {
       printf("Test script failed\n"); 
       return 1;
     }
     else
       printf("Test script passed\n");
     return 0;
     
}
     
     
    
       

   

