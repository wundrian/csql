//  Connect to the Data source
//  select all the rows from the table 'emp'

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

   // fetch the rows from the table

   int eid1=100;
   char ename1[20]="jitu";
   float salary1 = 2000;
   
   ret = SQLPrepare(stmt,(unsigned char*)"select * from emp;",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLBindCol(stmt,1,SQL_C_SLONG,&eid1,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindCol(stmt,2,SQL_C_CHAR,ename1,sizeof(ename1),NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindCol(stmt,3,SQL_C_FLOAT,&salary1,0,NULL);
   checkrc(ret,__LINE__);

   int j,count=0;
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);

   printf("Fetching starts on 'emp' table\n ");
   while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
   {
     printf("eid=%d\tename=%s\tsalary=%f\n",eid1,ename1,salary1);
     count++;
   }
  ret = SQLCloseCursor(stmt);
  checkrc(ret,__LINE__);

  ret =SQLTransact(env,dbc,SQL_COMMIT);
  checkrc(ret,__LINE__);

  printf("Total row fetched=%d\n",count);
   
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
       
