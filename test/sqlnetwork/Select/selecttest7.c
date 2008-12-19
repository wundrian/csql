/*   create table T1 with two fields,
 *   insert 10 rows into the table ,
 *   call fetch without call execute,it returns NULL.

 *   Author : Jitendra Lenka
 */

#include<SqlNwConnection.h>
#include<SqlNwStatement.h>
#include<SqlFactory.h>
//#include<Info.h>
int main()
{
  DbRetVal rv = OK;
  AbsSqlConnection *con = new SqlNwConnection();
  con->setInnerConnection(NULL);
  SqlNwConnection *conn = (SqlNwConnection *)con;
  conn->setHost("localhost", 5678);
  rv  = con->connect("root","manager");
  if(rv!=OK)return 1;

  AbsSqlStatement *stmt = new SqlNwStatement();
  stmt->setInnerStatement(NULL);
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

 rv  = stmt->execute(rows);
  if(rv!=OK)
  {
    delete stmt;
    delete con;
    return 2;
 }
 printf("Table created\n");

 //  insert records

 strcpy(statement,"INSERT INTO T1 VALUES(?,?);");

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

//*******************************************

  strcpy(statement,"SELECT * FROM T1;");
  rv = stmt->prepare(statement);
  
  if(rv !=OK)
  {
     delete stmt;
     delete con;
     return 4;
  }

  
  stmt->bindField(1,&f1var);
  stmt->bindField(2,f2var);
  
  void *ret;
  count = 0;
  rv = con->beginTrans();
  if(rv!=OK)return 5;
  //stmt->execute(rows);
  while (stmt->fetch(rv)!=NULL && rv == OK) {
      printf("Test script failed\n");
   }
    if (rv!=OK) {
        printf("without execute, Fetch failed\n");
        strcpy(statement,"DROP TABLE T1;");
        rv = stmt->prepare(statement);
        rv = stmt->execute(rows);
        if(rv==OK){printf("Table dropped successfully\n");}
        delete stmt;
        delete con;
        return 0;
  }
  delete stmt;
  delete con;
  return 7;
}
                 
