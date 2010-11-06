/*
  Autoincrement test 
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT AUTO_INCREMENT,f4 BIGINT);
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(1, 10, 100, 1000);
  INSERT INTO t1 VALUES(1, 10, NULL, 1000);
  INSERT INTO t1 VALUES(1, 10, 200, 1000);
  INSERT INTO t1 VALUES(1, 10, 150, 1000); 
  INSERT INTO t1 VALUES(1, 10, 100, 1000); it should be failed due to primary key viloation
  SELECT * FROM t1;
*/
#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK) {
        delete con;
        return 1;
    }
    printf("Connection opened\n");
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
//Creating Table
    char statement[400];
    printf("CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT AUTO_INCREMENT,f4 BIGINT);\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT AUTO_INCREMENT,f4 BIGINT);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Inserting Records
    con->beginTrans();
    rows=0;
    printf("INSERT INTO t1 VALUES(1, 10, 100, 1000);\n");
    stmt->prepare("INSERT INTO t1 VALUES(1, 10, 100, 1000);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(1, 10, NULL, 1000);\n");
    stmt->prepare("INSERT INTO t1 VALUES(1, 10, NULL, 1000);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(1, 10, 200, 1000);\n");
    stmt->prepare("INSERT INTO t1 VALUES(1, 10, 200, 1000);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(1, 10, 150, 1000);\n");
    stmt->prepare("INSERT INTO t1 VALUES(1, 10, 150, 1000);");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(1, 10, 100, 1000);\n");
    stmt->prepare("INSERT INTO t1 VALUES(1, 10, 100, 1000);");
    rv=stmt->execute(rows);
    if(rv=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    con->commit();
    stmt->free();
    char f1var;
    short int f2var;
    int f3var;
    long long f4var;
    char f5var[20];
    char f6var[32];
    float f7var;
    double f8var;
    Date f9var;
    Time f10var;
    TimeStamp f11var;
    
//Fetching records after insert
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 7; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 8;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%i | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

