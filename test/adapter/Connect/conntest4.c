//  close the connection and call execute,it should fail.

//  Author : Jitendra Lenka

#include<AbsSqlStatement.h>
#include<SqlFactory.h>
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = SqlFactory::createConnection(CSqlAdapter);
  rv = con->connect("root","manager");
  if(rv !=OK)return 1;
  printf("Connection opened\n");

  AbsSqlStatement *stmt = SqlFactory::createStatement(CSqlAdapter);
  stmt->setConnection(con);
  char statement[200];
  strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20)); ");
  
  int rows=0;
  rv = stmt->prepare(statement);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 2;
  }
  printf("prepared successfully\n");
  
  rv = con->disconnect();
  
  if(rv!=OK)return 3;
  printf("Disconnect successfully\n");
  
      
   rv = stmt->execute(rows);
   if(rv == OK)
  {
    printf("Test script failed \n");
    delete stmt;
    return 4;
  }
  stmt->free();
  printf("Test script passed\n");
  delete stmt;
  delete con;
  return 0;
}  
