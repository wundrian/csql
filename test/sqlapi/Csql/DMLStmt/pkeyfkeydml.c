/*
  primary key and foreign key constraint checking(for all datatypes).
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP, primary key(f3));
  CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP, foreign key(f3) references t1(f3));
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  INSERT INTO t2 VALUES(10,110,111,11110,'CSQL10','LAKSHYA10',110.00,1111.00,'2010-10-10','10:10:10','2010-10-10 10:10:10');
  DELETE FROM t1 WHERE f3=111; It should fail
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
    printf("CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP,primary key(f3));\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP,primary key(f3));");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
    printf("CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP, foreign key(f3) references t1(f3));\n");
    strcpy(statement,"CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP, foreign key(f3) references t1(f3));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
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
    con->beginTrans();
    rows=0;
    printf("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');\n");
    stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    stmt->execute(rows);

    printf("INSERT INTO t2 VALUES(10,110,111,11110,'CSQL10','LAKSHYA10',110.00,1111.00,'2010-10-10','10:10:10','2010-10-10 10:10:10');\n");
    stmt->prepare("INSERT INTO t2 VALUES(10,110,111,11110,'CSQL10','LAKSHYA10',110.00,1111.00,'2010-10-10','10:10:10','2010-10-10 10:10:10');");
    stmt->execute(rows);

    printf("DELETE FROM t1 WHERE f3=111;\n");
    rv = stmt->prepare("DELETE FROM t1 WHERE f3=111;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 9; }
    printf("Record can not be deleted from parrent because there exist a record in child record\n");
    
//Droping table
    strcpy(statement,"DROP TABLE t2;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Table dropped\n");
    stmt->free();
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

