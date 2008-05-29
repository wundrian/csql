/*  create table T1 ,Insert some records in it.
 *  Close the connection, Fetch should fail.

 *  Author : Jitendra Lenka
 */


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
   strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");
   
   int rows = 0;
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 2; }

   rv = stmt->execute(rows);
   if(rv!=OK) { delete stmt; delete con; return 3; }
   stmt->free();
   printf("Table T1 CREATED\n");
   
   // insert into statement  
   strcpy(statement,"INSERT INTO T1 VALUES(1,1);");
   rv = stmt->prepare(statement);
   if(rv!=OK) { delete stmt; delete con; return 4; }

   rv = con->beginTrans();
   if(rv!=OK) { delete stmt; delete con; return 5; }
   
   rv = stmt->execute(rows); if(rv!=OK) return 6;
   rv = con->commit();
   if(rv!=OK) return 7;
   stmt->free();
   printf("One record inserted\n");
   
    strcpy(statement,"SELECT F2 FROM T1 ;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 10; }

    int id=10;
    stmt->bindField(1,&id);
    rv = con->beginTrans();
    if(rv!=OK)return 11;
    stmt->execute(rows);
    int count=0;
    stmt->close();
	stmt->free();
    rv = con->disconnect(); //close the connection 
     
    void *rettype;
    if(rv!=OK)return 8;
    rettype = (char*)stmt->fetch();
    if(rettype==NULL && rv == OK) {
        printf("After closing the connection,fetch failed\n");
		con->connect("root", "manager");
		stmt->setConnection(con);
        strcpy(statement,"DROP TABLE T1;");
        rv = stmt->prepare(statement);
        rv = stmt->execute(rows);
        if(rv==OK){printf("Table Dropped successfully\n");}
		stmt->free();
        delete stmt;
        delete con;
		printf("Test script passed\n");
        return 0;
    }
        
    printf("Test script Failed\n");
    delete stmt;
    delete con;
    return 7;
}  
        

      
