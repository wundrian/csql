//  create table t1 ,Insert some records in it.
//  Close the connection, Fetch should fail.

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
   else if(strcmp(getenv("DSN"),"db2")==0)
       strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT)");
   else
       strcpy(statement,"CREATE TABLE t1(f1 INT,f2 INT);");
   
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
   rv = con->commit();
   if(rv!=OK) return 7;
   stmt->free();
   printf("One record inserted\n");
   
   strcpy(statement,"SELECT f2 FROM t1 ;");
   if(strcmp(getenv("DSN"),"db2")==0){
       strcpy(statement,"SELECT f2 FROM t1");
   }
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }

    int id=10;
    stmt->bindField(1,&id);
    rv = con->beginTrans();
    if(rv!=OK)return 9;
    stmt->execute(rows);
    int count=0;
    stmt->close();
	stmt->free();
    rv = con->disconnect(); //close the connection 
     
    void *rettype;
    if(rv!=OK)return 10;
    rettype = (char*)stmt->fetch(rv);
    if(rettype==NULL && rv == ErrNoConnection) {
        printf("After closing the connection,fetch failed\n");
		con->connect("root", "manager");
		stmt->setConnection(con);
        strcpy(statement,"DROP TABLE t1;");
        if(strcmp(getenv("DSN"),"db2")==0){
            strcpy(statement,"DROP TABLE t1");
        }
        rv = stmt->prepare(statement);
        rv = stmt->execute(rows);
        if(rv==OK){printf("Table Dropped successfully\n");}
	stmt->free();
        con->commit();
        delete stmt;
        delete con;
		printf("Test script passed\n");
        return 0;
    }
        
    printf("Test script Failed\n");
    delete stmt;
    delete con;
    return 11;
}  
        

      
