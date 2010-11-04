//Test for table exist in tdb or not
// 

#include"common.h"
#include <SqlOdbcStatement.h>
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
       strcpy(statement,"CREATE TABLE t1(f1 number(9),f2 number(9),primary key(f1));");
   else if(strcmp(getenv("DSN"),"db2")==0)
       strcpy(statement,"CREATE TABLE t1(f1 INT NOT NULL,f2 INT,primary key(f1))");
   else
       strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT,primary key(f1));");
   
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 2; }

   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 3; }
   stmt->free();
   printf("Table t1 CREATED\n");
   con->commit();   
   // insert into statement  
   printf("TableExists in Tdb Testing Starts Here\n");
   char pkfield[200];
   SqlOdbcStatement *oStmt= (SqlOdbcStatement *)stmt;
   bool tabflag=oStmt->isTableExists("t1");
   if(tabflag)
   {
      printf("Table t1 exists in TDB\n");
   }else{
      printf("Table t1 does not exists in TDB\n");
   }


   strcpy(statement,"DROP TABLE t1;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"DROP TABLE t1");
   }
   rv = stmt->prepare(statement);
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
   con->commit();
   tabflag=oStmt->isTableExists("t1");
   if(tabflag)
   {
      printf("Table t1 exists in TDB\n");
   }else{
      printf("Table t1 does not exists in TDB\n");
   }

   printf("Table droped\n");

   delete stmt;
   delete con;
   return 0;
}  
        

      
