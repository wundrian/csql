//  create table t1 , insert  and update
//  then rollback. All Should Work Fine

#include "common.h"
int main()
{
   DbRetVal rv = OK;
   AbsSqlConnection *con = createConnection();
   rv = con->connect("root","manager");
   if(rv !=OK)return 1;
   printf("Connection opened\n");
   
   AbsSqlStatement *stmt = createStatement();
   stmt->setConnection(con);
   char statement[200];
   if(strcmp(getenv("DSN"),"oracle")==0)
        strcpy(statement,"CREATE TABLE t1(f1 number(9),f2 number(9));");
   else if(strcmp(getenv("DSN"),"psql")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT) ;");
   else if(strcmp(getenv("DSN"),"sybase")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT) ;");
   else if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT)");
   else
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT) engine='innodb';");
   
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 1;
   }

   rv = stmt->execute(rows);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 2;
   }
   con->commit();
   stmt->free();
   printf("Table t1 CREATED\n");
   
   strcpy(statement,"INSERT INTO t1 VALUES(1,1);");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"INSERT INTO t1 VALUES(1,1)");
   }
   rv = stmt->prepare(statement);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 3;
   }

   rv = con->beginTrans();
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 4;
   }
   
   rv = stmt->execute(rows);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 5;
   }      
   printf("1 Record inserted\n");
   stmt->free();

   strcpy(statement,"UPDATE t1 SET f2=100;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"UPDATE t1 SET f2=100");
   }
   
   rv = stmt->prepare(statement);
   if(rv !=OK)
   {
      delete stmt;
      delete con;
      return 6;
   }

    
    rv = stmt->execute(rows);
    if(rv!=OK && rows !=1)return 7;
    printf("1 Record updated\n"); 
    //  ROLLBACK  
    
    rv  = con->rollback();
    if(rv!=OK)return 8;
    
    stmt->free();

    strcpy(statement,"SELECT f2 FROM t1 ;");
    if(strcmp(getenv("DSN"),"db2")==0){
        strcpy(statement,"SELECT f2 FROM t1");
    }
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
      delete stmt;
      delete con;
      return 9;
    }

    int id=10;
    stmt->bindField(1,&id);
    rv = con->beginTrans();
    if(rv!=OK)return 1;
    stmt->execute(rows);
    int count=0;
    while(stmt->fetch()!=NULL)
    {
      printf("f2= %d\n",id);
      count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv!=OK)return 10;

    printf("Total record fetched =%d ,Because transaction rollbacked\n",count); 
   stmt->free();

    strcpy(statement,"DROP TABLE t1;");
    if(strcmp(getenv("DSN"),"db2")==0){
        strcpy(statement,"DROP TABLE t1");
    }
    rv = stmt->prepare(statement);
    if(rv!=OK)
    {
      delete stmt;
      delete con;
      return 11;
    }
    rv = stmt->execute(rows);
    if(rv!=OK)
    {
      delete stmt;
      delete con;
      return 12;
    }
    con->commit();
    printf("Table droped\n");
    stmt->free();
    delete stmt;
    delete con;
    return 0;
}
      
