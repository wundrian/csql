//  INSERT SOME TUPLES IN IT. AND FETCH ALL THE TUPLES.


#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>

     
    
//*************************************************************************
// ERROR CHECK FUNCTION
inline void checkrc(int rc,int line)
{
   if(rc)
   {
       printf("ERROR %d at line %d\n",rc,line);
       exit(1);
   }
}

//*************************************************************************
// FUNCTION FOR INSERTING ROWS IN IT.
int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      int ret;
      int f1=50; // f1 field
      char f2[50]= "Praba";
      SQLINTEGER slen = SQL_NTS;
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER FOR ALL THE FIELD

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f2,0,&slen);
      checkrc(ret,__LINE__);

      int i,count=0;
      // EXECUTE THE STATEMENT
      for(i=0;i<10;i++)
      {
         f1++;
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
  }
//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      char f2[50]= "jitendra";

     ret = SQLPrepare(stmt,(unsigned char*)"SELECT * FROM T1",SQL_NTS);
     checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,NULL);
    checkrc(ret,__LINE__);


    ret = SQLBindCol(stmt,2,SQL_C_CHAR,f2,sizeof(f2),NULL);
    checkrc(ret,__LINE__);
 
    int j, count=0;
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    printf("Fetching starts on table  T1 :\n");
    
    while(SQL_SUCCEEDED(ret = SQLFetch(stmt)))
    {
        printf("F1=%d\tF2=%s\n ",f1,f2);
        count++;
    }
    
    ret = SQLCloseCursor(stmt);
    checkrc(ret,__LINE__);
    
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    printf("Total row fetched=%d\n",count);
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
  ret =  SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
  checkrc(ret,__LINE__); 
  //ALLOCATE A Connection handle
  ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
  checkrc(ret,__LINE__);
    
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=test;MODE=Gateway;SERVER=localhost;PORT=5678;", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));
 
  if(SQL_SUCCEEDED(ret))
  {
     printf("\nConnected to the Data Source SUCCESSFULLY..\n");
     
 
  }
   else
   {
        printf("error in connection\n");                
        return 1;
 
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__);
        return 1;      
   
  }

   
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   //****************************************************************
   InsertTest(env,dbc,stmt);  
   FetchTest(env,dbc,stmt);

   //****************************************************************      
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
