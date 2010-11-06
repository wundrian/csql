/*Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
  * create table Ti with one integer field and one char field. insert some records into it.
   delete from t1 where f1=10.
   sqlrowcount() should return 1. 
   
   delete from t1 where f1 > 900
   sqlrowcount shpuld return 100.
   
   insert one record with values(1001,'1000')
   sqlrowcount should return 1.
   
   update T1 set f2='thousand' where f1<10.
   sqlrowcount() should return 9


   AUTHOR : Jitendra Lenka

*/


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

//*************************************************************************
int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      SQLRETURN  ret;
      int f1=0; // f1 field
      char f2[15]="jitendra";//f2 field
      SQLINTEGER slen=SQL_NTS;
      
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_LONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f2,0,&slen);
      checkrc(ret,__LINE__);

    

      int i,count=0;
      for(i=0;i<1000;i++)
      {
         f1++;
         
         
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
        
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }
//***********************************************************************


 
 
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
                   (SQLCHAR *) "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;"),
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
     "CREATE TABLE T1(F1 INT,F2 char(30))";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("\nTABLE CREATED\n"); 
   //****************************************************************
   
   //  INSERT FUNCTION
   InsertTest(env,dbc,stmt);  
   //*****************************************************************
   // DELETE FROM T1;
   printf("delete from T1 where F1=10\n");
   SQLCHAR delete1[50]="DELETE FROM T1 WHERE F1=10;"; 

  ret = SQLPrepare(stmt,delete1,SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   
   
   SQLINTEGER nor;
   ret = SQLRowCount(stmt,&nor);
   printf("sqlrowcount() returns=%d\n",nor); //  nor should return 1.
   if(nor!=1)return 1;
   ret = SQLFreeStmt(stmt,SQL_RESET_PARAMS);
   checkrc(ret,__LINE__);
   //************************************************
   
   printf("\ndelete from T1 where F1 > 900\n");
   ret = SQLPrepare(stmt,(unsigned char*)"DELETE FROM T1 WHERE F1 > 900",SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   SQLINTEGER nor1;
   ret = SQLRowCount(stmt,&nor1);
   printf("sqlrowcount() returns=%d\n",nor1);
   if(nor1!=100)return 1;

   ret = SQLFreeStmt(stmt,SQL_RESET_PARAMS);
   checkrc(ret,__LINE__);
   //*************************************************************
   printf("\ninsert into T1 values(1001,'1000')\n");
   ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(1001,'1000')",SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   SQLINTEGER nor2;
   ret = SQLRowCount(stmt,&nor2);
   checkrc(ret,__LINE__);

   printf("sqlrowcount() returns=%d\n",nor2);
   if(nor2!=1)return 1;
   ret = SQLFreeStmt(stmt,SQL_RESET_PARAMS);
   
   //*****************************************************
   printf("\nUPDATE T1 SET F2='THOUSAND' WHERE F1<10\n");
   ret = SQLPrepare(stmt,(unsigned char*)"UPDATE T1 SET F2='THOUSAND' WHERE F1<10",SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   
   SQLINTEGER nor3;
   ret = SQLRowCount(stmt,&nor3);
   
   checkrc(ret,__LINE__);
   printf("sqlrowcount()  returns=%d\n",nor3);
   if(nor3!=9)return 1;
   /*ret = SQLFreeStmt(stmt,SQL_RESET_PARAMS);
   checkrc(ret,__LINE__);*/
   //***********************************************
   
   //FetchTest(env,dbc,stmt);

   //****************************************************************      
   //drop the table
   ret = SQLPrepare(stmt,(unsigned char*)"drop table T1;",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("Table 'T1' dropped\n");

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
