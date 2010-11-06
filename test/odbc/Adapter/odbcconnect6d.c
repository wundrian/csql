//connect to the DATA SOURCE with the connection string "DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;"
// close the connection and then call fetch,it should fail.

// AUTHOR : Jitendra Lenka

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
     "CREATE TABLE T1(F1 INT,F2 INT)";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
    printf("\nTABLE CREATED\n"); 
   //****************************************************************
   // insert tuple into table
   ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(100,200)",SQL_NTS);
   checkrc(ret,__LINE__);
   
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__); 
   //*****************************************************************
   // FETCHING ROWS FROM TABLE
   int f1=1;
   int f2=2;
   ret = SQLPrepare(stmt,(unsigned  char*)"SELECT * FROM T1",SQL_NTS);
   checkrc(ret,__LINE__);

   ret = SQLBindCol(stmt,1,SQL_C_LONG,&f1,0,NULL);
   checkrc(ret,__LINE__);

   ret = SQLBindCol(stmt,2,SQL_C_LONG,&f2,0,NULL);
   checkrc(ret,__LINE__);
   
   int j,count=0;
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);

   //close the connection
   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   
   // after closing call fetch.
   int rettype; 
   while(SQL_SUCCEEDED(ret =SQLFetch(stmt)))
   {
      
     if(ret )
        printf("After disconnect, Fetch failed\n");
      else
        count++;
   }
   rettype=ret;
   printf("Number of rows are fetched=%d\n",count);

   
  //  *****************************************************************
  //  again connect for drop the table
   
  
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;", (SQLSMALLINT) strlen ("DSN=mycsql;MODE=ADAPTER;SERVER=127.0.0.1;PORT=5678;"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));


  if(SQL_SUCCEEDED(ret))
  {
     printf("\nagain Connected to the Data Source successfully..\n");

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
   

         ret = SQLPrepare(stmt,(unsigned char*)"drop table T1;",SQL_NTS);
         checkrc(ret,__LINE__);

         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__); 
         printf("Table dropped\n");
     

   //****************************************************************      
   ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   if(rettype == 0) return 1;
   printf("After closing the connection, fetch does not work\n");
   return 0;
}         
