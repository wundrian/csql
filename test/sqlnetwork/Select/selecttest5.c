/*   call execute without calling prepare. it should fail.
     
 *   Author : Jitendra Lenka
 */

#include<SqlNwConnection.h>
#include<SqlNwStatement.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = new SqlNwConnection();
  con->setInnerConnection(NULL);
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = new SqlNwStatement();
  stmt->setInnerStatement(NULL);
  stmt->setConnection(con);
  char statement[200];

  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");

  int rows=0;
  /*rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 1;
 }*/

 rv  = stmt->execute(rows);
 if(rv!=OK)
  {
    delete stmt;
    delete con;
    printf("Execute failed without call prepare\n");
    return 0;
 }
 printf("Test script failed\n");

   
   delete stmt;
   delete con;
   return 1;
 }
  
