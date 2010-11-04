/*   prepare,execute,prepare....,
 *   second prepare should pass.
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
   printf("Prepared the statement\n");
 
   rv  = stmt->execute(rows);
   if(rv!=OK)
   {
     delete stmt;
     delete con;
     return 2;
   }
   printf("Execute the statement\n");
   con->commit(); 
  
  //again prepare

  strcpy(statement,"DROP TABLE t1;");
  if(strcmp(getenv("DSN"),"db2")==0)
      strcpy(statement,"DROP TABLE t1");
  rv = stmt->prepare(statement);
  if(rv!=OK)
  {
     printf("Test script failed\n");
     return 3;
  }
  
  printf("Test script passed\n");
  stmt->execute(rows);
  con->commit();
  stmt->free();
  delete stmt;
  delete con;
  return 0;
}
