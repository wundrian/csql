//  Connect to the Data source
//  delete rows from the table
#include<stdio.h>
#include<stdlib.h>
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

   
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);

   // delete 5 rows from the table with parameter.

   int eid1;

   ret = SQLPrepare(stmt,(unsigned char*)"delete from emp where eid = ?;",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&eid1,0,NULL);
   checkrc(ret,__LINE__);

   int i,count=0;
   
   eid1=5000;
   for(i=0;i<5;i++)
   {
     eid1++;
     ret = SQLExecute(stmt);
     checkrc(ret,__LINE__);

     ret = SQLTransact(env,dbc,SQL_COMMIT);
     checkrc(ret,__LINE__);

     ret = SQLTransact(env,dbc,SQL_COMMIT);
     count++;
   }
   printf("Deleted first %d updated rows in 'emp' table\n",count);

   // delete all the rows from the table
   ret = SQLPrepare(stmt,(unsigned char*)"delete from emp;",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   ret = SQLTransact(env,dbc,SQL_COMMIT);
   checkrc(ret,__LINE__);

   printf("All the rows are deleted \n");   
      
   // drop the table from the table

   SQLCHAR drop[30]="drop table emp;";
   
   ret = SQLExecDirect(stmt,drop,SQL_NTS);
   checkrc(ret,__LINE__);

      
   printf("Table 'emp'dropped successfully\n");
   
   

   ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);
   
   ret - SQLDisconnect(dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);

   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   return 0;
} 
       
