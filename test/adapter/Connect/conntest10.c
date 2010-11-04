//  Create table t1, INSERT, UPDATE AND COMMIT.
//  FETCH UPDATED RECORDS.

#include"common.h"
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
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT);");
   else if(strcmp(getenv("DSN"),"sybase")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT);");
   else if(strcmp(getenv("DSN"),"db2")==0)
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT)");
   else
        strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT) engine='innodb';");
   
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 2; }

   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 3; }
   stmt->free();
   printf("Table t1 CREATED\n");
   con->commit();   
   // insert into statement  
   strcpy(statement,"INSERT INTO t1 VALUES(1,1);");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"INSERT INTO t1 VALUES(1,1)");
   }
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 4; }

   rv = con->beginTrans();
   if(rv!=OK) { delete stmt; delete con; return 5; }
   
   rv = stmt->execute(rows); if(rv!=OK) return 6;
   stmt->free();
   printf("One record inserted\n");
   
   // update statement 

   printf("update t1 set f2=100\n");
   strcpy(statement,"UPDATE t1 SET f2=100;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"UPDATE t1 SET f2=100");
   } 
   rv = stmt->prepare(statement);
   if(rv !=OK) { delete stmt; delete con; return 7; }

   rv = stmt->execute(rows);
   if(strcmp(getenv("DSN"),"db2")!=0){
     if(rv!=OK){ printf ("Hello\n"); return 8; }
   }
   rv  = con->commit(); if(rv!=OK)return 9;
   printf("One row updated\n");

   strcpy(statement,"SELECT f2 FROM t1 ;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"SELECT f2 FROM t1");
   }
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 10; }

   int id=10;
   stmt->bindField(1,&id);
   rv = con->beginTrans();
   if(rv!=OK)return 11;
   stmt->execute(rows);
   int count=0;
   while(stmt->fetch()!=NULL)
   {
     printf("f2= %d\n",id);
     count++;
   }
   stmt->close();
   rv = con->commit();
   if(rv!=OK)return 12;
   printf("Total reccord fetchec=%d\n",count);
   stmt->free();
   strcpy(statement,"DROP TABLE t1;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"DROP TABLE t1;");
   }
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 13; }
   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 14; }
   con->commit();
   printf("TABLE t1 DROPPED SUCCESSFULLY\n");
   stmt->free();
   delete stmt;
   delete con;
   printf("Connection closed successfully\n");
   return 0;
}    
