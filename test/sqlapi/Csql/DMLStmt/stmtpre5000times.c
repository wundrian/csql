/*
  Statement prepare and execute 5000 times .
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);
  prepare and execute the below statement 5000 times
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1',11.11,1111.11,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  select count(*) should display 5000 records
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
    printf("CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(10),f6 FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(10),f6 FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);");
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
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Inserting Records
    rows=0;
    int i=0;
    con->beginTrans();
    for(i=8; i<= 5007; i++)
    {
	stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1',11.11,1111.11,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
        if(rv!=OK) { delete stmt; con->disconnect(); delete con; return i; }
	stmt->execute(rows);
        if(rv!=OK) { delete stmt; con->disconnect(); delete con; return i+1; }
    }
    con->commit();
    stmt->free();

    int cnt=0;
    
//Fetching records after insert
    printf("SELECT COUNT(*) FROM t1;\n");
    strcpy(statement,"SELECT COUNT(*) FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5008; }
    stmt->bindField(1,&cnt);
    rv = con->beginTrans();
    if(rv!=OK)return 9;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
        printf("t1.COUNT(*)\n-----------\n  %d \n", cnt);
    }
    stmt->free();
    rv = con->commit();    
      
//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5009; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5010; }
    printf("Table t1 dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

