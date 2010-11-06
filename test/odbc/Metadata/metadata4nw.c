/* Use Connection String "DSN=mycsql;MODE=csql;SERVER=127.0.0.1;PORT=5678;" for Connect Data Source
 * CREATE TABLE "T1" WITH 10 FIELDS.
    SQLColumns()  Should return all field infomation

*/

#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
#include<CSql.h>    
#define STR_LEN 128 + 1
#define REM_LEN 254 + 1

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

int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
      int ret;

    SQLCHAR szSchema[STR_LEN];
    SQLCHAR szCatalog[STR_LEN];
    SQLCHAR szColumnName[STR_LEN];
    SQLCHAR szTableName[STR_LEN];
    SQLCHAR szTypeName[STR_LEN];
    SQLCHAR szRemarks[REM_LEN];
    SQLCHAR szColumnDefault[STR_LEN];
    SQLCHAR szIsNullable[STR_LEN];

    SQLINTEGER ColumnSize;
    SQLINTEGER BufferLength;
    SQLINTEGER CharOctetLength;
    SQLINTEGER OrdinalPosition;

    SQLSMALLINT DataType;
    SQLSMALLINT DecimalDigits;
    SQLSMALLINT NumPrecRadix;
    SQLSMALLINT Nullable;
    SQLSMALLINT SQLDataType;
    SQLSMALLINT DatetimeSubtypeCode;

     ret = SQLColumns(stmt, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"", SQL_NTS, (SQLCHAR*)"T1", SQL_NTS, NULL, 0);
     checkrc(ret,__LINE__);
    short totalFields = 0 ;
    ret = SQLNumResultCols (stmt, &totalFields); 
    checkrc(ret,__LINE__);
    printf( "No of columns in resultset = %d\n",totalFields);
    
    
    SQLBindCol(stmt, 1, SQL_C_CHAR, szCatalog, STR_LEN,NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, szSchema, STR_LEN, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, szTableName, STR_LEN,NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, szColumnName, STR_LEN, NULL);
    SQLBindCol(stmt, 5, SQL_C_SSHORT, &DataType, 0, NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, szTypeName, STR_LEN, NULL);
    SQLBindCol(stmt, 7, SQL_C_SLONG, &ColumnSize, 0, NULL);
    SQLBindCol(stmt, 8, SQL_C_SLONG, &BufferLength, 0, NULL);
    SQLBindCol(stmt, 9, SQL_C_SSHORT, &DecimalDigits, 0, NULL);
    SQLBindCol(stmt, 10, SQL_C_SSHORT, &NumPrecRadix, 0, NULL);
    SQLBindCol(stmt, 11, SQL_C_SSHORT, &Nullable, 0, NULL);
    SQLBindCol(stmt, 12, SQL_C_CHAR, szRemarks, REM_LEN, NULL);
    SQLBindCol(stmt, 13, SQL_C_CHAR, szColumnDefault, STR_LEN, NULL);
    SQLBindCol(stmt, 14, SQL_C_SSHORT, &SQLDataType, 0, NULL);
    SQLBindCol(stmt, 15, SQL_C_SSHORT, &DatetimeSubtypeCode, 0,NULL);
    SQLBindCol(stmt, 16, SQL_C_SLONG, &CharOctetLength, 0, NULL);
    SQLBindCol(stmt, 17, SQL_C_SLONG, &OrdinalPosition, 0, NULL);
    SQLBindCol(stmt, 18, SQL_C_CHAR, szIsNullable, STR_LEN, NULL);

    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
       printf("szCatalog =%s \t szSchema=%s \t szTableName=%s \t szColumnName= %s \t DataType = %d ColumnSize = %d  Nullable =%d szRemarks = %s, OrdinalPosition =%d szIsNullable =%s\n ",szCatalog,szSchema,szTableName,szColumnName,DataType,ColumnSize,Nullable,szRemarks,OrdinalPosition,szIsNullable);
    }
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);

    ret = SQLTransact(env,dbc,SQL_COMMIT);
       checkrc(ret,__LINE__);
    return 0;
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
        printf("error in conenction\n");
     
         ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
         checkrc(ret,__LINE__);

         ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
         checkrc(ret,__LINE__);
         return 1;
   }

   
   //*****************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT,PRIMARY KEY(F2,F7,F1));";
   
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("\nTABLE CREATED\n"); 
   //***************************
   FetchTest(env,dbc,stmt);
   //**************************************************      
    SQLCHAR drop[100]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);
    ret = SQLExecute(stmt);
    if(ret!=SQL_SUCCESS && ret !=SQL_SUCCESS_WITH_INFO)
    {   
      printf("Statement failed\n");
       return 1;
    }

       printf("Table  dropped successfully\n");  

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
