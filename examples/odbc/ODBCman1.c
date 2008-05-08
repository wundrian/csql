//  Connect to the Data source

#include<stdio.h>
#include<stdlib.h>
#include<CSql.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
inline void checkrc(int rc, int line)
{
   if(rc)
   {
      printf("ERROR %d at line %d\n",rc,line);
      exit(1);
   }
}


int main()
{
   SQLHENV env;
   SQLHDBC dbc;
   SQLHSTMT stmt;
   SQLRETURN ret;
   SQLCHAR outstr[1024];
   SQLSMALLINT  outstrlen;
   
   ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
   checkrc(ret,__LINE__);

   ret = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
   checkrc(ret,__LINE__);

   ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
   checkrc(ret,__LINE__);
    ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));



   if(SQL_SUCCEEDED(ret))
   {
      printf("\nConnect to the data source successfully\n");
   }
   else
   {  
     printf("Failed to connect\n");
     return 2;
   }

   ret - SQLDisconnect(dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   return 0;
} 
       
