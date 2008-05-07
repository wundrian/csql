/*   prepare,execute,prepare....,
 *   second prepare should fail saying "stmt not freed"

 *   Author : Jitendra Lenka
 */

#include<AbsSqlStatement.h>
#include<SqlFactory.h>
//#include<Info.h>
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = SqlFactory :: createConnection(CSql);
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = SqlFactory :: createStatement(CSql);
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20));");

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
 
  
  //again prepare

  strcpy(statement,"DROP TABLE T1;");
  rv = stmt->prepare(statement);
  if(rv==OK)
  {
     printf("Test script failed\n");
     return 3;
  }
  printf("Test script passed\n");
  stmt->free();
  delete stmt;
  delete con;
  return 0;
}
