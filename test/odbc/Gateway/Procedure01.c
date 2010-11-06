#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
inline void checkrc(int rc,int line)
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
  SQLSMALLINT outstrlen;

   ret=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
   checkrc(ret,__LINE__);
   SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);

   ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
   checkrc(ret,__LINE__);
//   ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*)"DSN=myodbc3;", SQL_NTS, outstr, sizeof(outstr), &outstrlen,SQL_DRIVER_NOPROMPT);
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=ADAPTER;SERVER=localhost;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=ADAPTER;SERVER=localhost;PORT=5678;"),
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
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
///=====================
    //char f1[20]="india is best";
   int f1=0;
   int f2=0;
   SQLCHAR inout[124]="{call CsqlRef.InParamSelect(15) }";
   ret = SQLPrepare(stmt,inout,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
      
   ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,NULL);
   checkrc(ret,__LINE__);
   ret = SQLBindCol(stmt,2,SQL_C_SLONG,&f2,0,NULL);
   checkrc(ret,__LINE__);
  
   while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
         printf("F1=%d F2=%d \n",f1,f2);
   }

   ret = SQLCloseCursor(stmt);
   checkrc(ret,__LINE__);

   ret = SQLTransact(env,dbc,SQL_COMMIT);
   checkrc(ret,__LINE__);
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

