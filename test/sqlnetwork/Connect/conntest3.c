/*  close the connection and call prepare ,it should fail

 *  Author : Jitendra Lenka
 */
#include<SqlNwConnection.h>
#include<SqlNwStatement.h>
#include<SqlFactory.h>

int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = new SqlNwConnection();
  con->setInnerConnection(NULL);
  rv = con->connect("root","manager");
  if(rv !=OK)return 1;
  printf("Connection opened\n");

  AbsSqlStatement *stmt = new SqlNwStatement();
  stmt->setInnerStatement(NULL); 
  stmt->setConnection(con);
  char statement[200];
  strcpy(statement,"CREATE TABLE T1(F1 INT);");
  
  int  rows;
  rv = con->disconnect();
  if(rv!=OK)return 2;
  printf("Connection closed\n"); 
  
  rv = stmt->prepare(statement);
  if(rv==OK)
  {
     
     delete stmt;
     delete con;
     printf("Test script failed\n");
     return 3;
  }
  printf("Test script passed\n");
  delete stmt;
  delete con;
  return 0;
}
  
  
