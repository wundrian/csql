/*  create table T1 , insert  and update
 *  then rollback, 

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
   strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");
   
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 1; }

   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 2; }

   printf("Table T1 CREATED\n");

   strcpy(statement,"INSERT INTO T1 VALUES(1,1);");
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 3; }

   rv = con->beginTrans();
   if(rv!=OK) { delete stmt; delete con; return 4; }
   
   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 5; }      
   printf("1 Record inserted\n");

   strcpy(statement,"UPDATE T1 SET F2=100;");
   
   rv = stmt->prepare(statement);
   if(rv !=OK) { delete stmt; delete con; return 6; }

    rv = stmt->execute(rows);
    if(rv!=OK && rows !=1)return 7;
    printf("1 Record updated\n"); 
    //  ROLLBACK  
    
    rv  = con->rollback();
    if(rv!=OK)return 8;
    
    strcpy(statement,"SELECT F2 FROM T1 ;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 9; }

    int id=10;
    stmt->bindField(1,&id);
    rv = con->beginTrans();
    if(rv!=OK)return 1;
    stmt->execute(rows);
    int count=0;
    while(stmt->fetch()!=NULL) { printf("F2= %d\n",id); count++; }
    stmt->close();
    rv = con->commit();
    if(rv!=OK)return 10;

    printf("Total record fetched =%d ,Because transaction rollbacked\n",count); 

    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 11; } 
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 12; }
    printf("Table droped\n");
    delete stmt;
    delete con;
    return 0;
}
      
