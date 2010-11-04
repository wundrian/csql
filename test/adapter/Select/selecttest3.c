/*   create table t1 with two fields,
 *   insert 10 rows into the table ,
 *   select from nonexisting table.
*/

#include "common.h"
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = createConnection();
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = createStatement();
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE t1(f1 INT,f2 CHAR(20));");
  if(strcmp(getenv("DSN"),"db2")==0)
  	strcpy(statement,"CREATE TABLE t1(f1 INT,f2 CHAR(20))");

  int rows=0;
  rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 1;
 }

 rv  = stmt->execute(rows);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 2;
 }
 stmt->free();
 printf("Table created\n");
 con->commit();
 //  insert records

 strcpy(statement,"INSERT INTO t1 VALUES(?,?);");
  if(strcmp(getenv("DSN"),"db2")==0)
 	strcpy(statement,"INSERT INTO t1 VALUES(?,?)");

 int f1var = 1;
 char f2var[20] = "lakshya";
 

 rv = stmt->prepare(statement);
 if(rv!=OK)
 {
   delete stmt;
   delete con;
   return 3;
 }

 int count=0;

 for(int i=0;i<2;i++)
 {
    
   for(int j=0;j<5;j++)
    {	
        f1var = j;
        rv = con->beginTrans();
	if(rv!=OK)break;
	
         	
        stmt->setIntParam(1,f1var);
	stmt->setStringParam(2,f2var);

	rv = stmt->execute(rows);
	if(rv!=OK)break;
	rv = con->commit();
	if(rv!=OK)break;
	count++;
    }
    printf("%d rows inserted\n",count);
 }
 stmt->free();

//*******************************************

  strcpy(statement,"SELECT * FROM t11;");
  if(strcmp(getenv("DSN"),"db2")==0)
  	strcpy(statement,"SELECT * FROM t11");
  rv = stmt->prepare(statement);
  
  if(rv !=OK)
  {
      printf("test script passed\n");
      strcpy(statement,"DROP TABLE t1;");
      if(strcmp(getenv("DSN"),"db2")==0)
          strcpy(statement,"DROP TABLE t1");
      rv = stmt->prepare(statement);
      rv = stmt->execute(rows);
      if(rv==OK){printf("Table dropped\n");}
     stmt->free();
     con->commit();
     delete stmt;
     delete con;
     return 0;
  }

  else if(rv==OK)
  {
     if(strcmp(getenv("DSN"),"oracle")==0 || strcmp(getenv("DSN"),"psql")==0 || strcmp(getenv("DSN"),"sybase")==0)
     {
         printf("Test script Passed\n");
         strcpy(statement,"DROP TABLE t1;");
         if(strcmp(getenv("DSN"),"db2")==0)
             strcpy(statement,"DROP TABLE t1");
         rv = stmt->prepare(statement);
         rv = stmt->execute(rows);
         if(rv==OK){printf("Table dropped\n");}
         stmt->free();
         con->commit();
         delete stmt;
         delete con;
         return 0; 
     }
     else
     {
	 printf("Test script failed\n");
         strcpy(statement,"DROP TABLE t1;");
         if(strcmp(getenv("DSN"),"db2")==0)
             strcpy(statement,"DROP TABLE t1");
         rv = stmt->prepare(statement);
         rv = stmt->execute(rows);
         if(rv==OK){printf("Table dropped\n");}
         stmt->free();
         con->commit();
         delete stmt;
         delete con;
         return 5;
     }
  }  
 else
 {
  stmt->bindField(1,&f1var);
  stmt->bindField(2,f2var);
  

  count = 0;
  rv = con->beginTrans();
  if(rv!=OK)return 6;
  stmt->execute(rows);
  while(stmt->fetch()!=NULL)
  {
     count++;
  }

  stmt->close();
  rv = con->commit();
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 7;
  }

  printf("Total row fetched=%d\n",count);
  
 }  
  stmt->free();
  con->commit();
   
  delete stmt;
  delete con;
  return 0;
}
 

 
