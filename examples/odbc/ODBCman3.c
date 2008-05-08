//  Connect to the Data source
//  insert 10 rows in it.
  
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


   // inserting records into the table.

   int eid1 = 1000;
   char ename1[20]="jitu";
   float salary1 = 5500;
   char ename2[10][20]= {"Praba","Kishor","Jitu","Sanjit","Sanjay","Bisi","Suman","Vikrant","Eti","Suba"};   
   SQLINTEGER slen=SQL_NTS;
   
   ret = SQLPrepare(stmt,(unsigned char*)"insert into emp values(?,?,?);",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&eid1,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)ename1,0,&slen);
   checkrc(ret,__LINE__);
   
   ret = SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&salary1,0,NULL);
   checkrc(ret,__LINE__);
   int i;
   int count=0;
   for( i=0;i<10;i++)
   {
     eid1++;
     salary1 = salary1 + 1000;
     strcpy(ename1,ename2[i]);
     ret = SQLExecute(stmt);
     checkrc(ret,__LINE__);
     
     ret = SQLTransact(env,dbc,SQL_COMMIT);
     checkrc(ret,__LINE__);
   
     count++;
   }
   printf("%d rows inserted in 'emp' table\n",count);

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
       
