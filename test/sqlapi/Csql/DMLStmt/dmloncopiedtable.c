/*
 Basic DML on copied table
  CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);
  create table t1 as select * from t2;
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1',11.11,1111.11,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2',22.22,2222.22,'2002-02-02','02:02:02','2002-02-02 02:02:02');
  UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB', f6=f6+100, f7=f7+10000,f8='2009-11-20', f9='12:01:01', f10='2009-11-20 12:01:01' WHERE f1<=3;
  DELETE FROM t1 WHERE f1=12 OR f1=4;
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
    printf("CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);\n");
    strcpy(statement,"CREATE TABLE t2(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 FLOAT,f7 DOUBLE,f8 DATE,f9 TIME,f10 TIMESTAMP);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
//copy table 
    printf("CREATE TABLE t1 AS SELECT * FROM t2;\n");
    strcpy(statement,"CREATE TABLE t1 AS SELECT * FROM t2;");
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
    printf("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1',11.11,1111.11,'2001-01-01','01:01:01','2001-01-01 01:01:01');\n");
    stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1',11.11,1111.11,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2',22.22,2222.22,'2002-02-02','02:02:02','2002-02-02 02:02:02');\n");
    stmt->prepare("INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2',22.22,2222.22,'2002-02-02','02:02:02','2002-02-02 02:02:02');");
    stmt->execute(rows);
    con->commit();
    stmt->free();

    char f1var;
    short int f2var;
    int f3var;
    long long f4var;
    char f5var[20];
    float f6var;
    double f7var;
    Date f8var;
    Time f9var;
    TimeStamp f10var;
    
//Fetching records after insert
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,&f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 9;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(float)=NULL | ");
        else printf("f6(float)=%f | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(double)=NULL | ");
        else printf("f7(double)=%lf | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(date)=NULL | ");
        else printf("f8(date)=%02d-%02d-%02d | ", f8var.year(),f8var.month(),f8var.dayOfMonth());
	if(stmt->isFldNull(9)) printf("f9(time)=NULL | ");
        else printf("f9(time)=%02d:%02d:%02d | ", f9var.hours(),f9var.minutes(),f9var.seconds());
	if(stmt->isFldNull(10)) printf("f10(timestamp)=NULL | ");
        else printf("f10(timestamp)=%d-%d-%d %d:%d:%d | ", f10var.year(),f10var.month(),f10var.dayOfMonth(),f10var.hours(),f10var.minutes(),f10var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
      
 
//Updating records.
    con->beginTrans();
    printf("UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB', f6=f6+100, f7=f7+10000,f8='2009-11-20', f9='12:01:01', f10='2009-11-20 12:01:01' WHERE f1<=3;\n");
    strcpy(statement,"UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB', f6=f6+100, f7=f7+10000,f8='2009-11-20', f9='12:01:01', f10='2009-11-20 12:01:01' WHERE f1<=3;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    con->commit();
    stmt->free();

//Fetching records after update
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 12; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,&f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 13;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(float)=NULL | ");
        else printf("f6(float)=%f | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(double)=NULL | ");
        else printf("f7(double)=%lf | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(date)=NULL | ");
        else printf("f8(date)=%02d-%02d-%02d | ", f8var.year(),f8var.month(),f8var.dayOfMonth());
	if(stmt->isFldNull(9)) printf("f9(time)=NULL | ");
        else printf("f9(time)=%02d:%02d:%02d | ", f9var.hours(),f9var.minutes(),f9var.seconds());
	if(stmt->isFldNull(10)) printf("f10(timestamp)=NULL | ");
        else printf("f10(timestamp)=%d-%d-%d %d:%d:%d | ", f10var.year(),f10var.month(),f10var.dayOfMonth(),f10var.hours(),f10var.minutes(),f10var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
      
  
//Deleting Records.
    con->beginTrans();
    printf("DELETE FROM t1 WHERE f1=12 OR f1=4;\n");
    strcpy(statement,"DELETE FROM t1 WHERE f1=12 OR f1=4;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    con->commit();
    stmt->free();

//Fetching records after delete
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 16; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,&f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 17;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(float)=NULL | ");
        else printf("f6(float)=%f | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(double)=NULL | ");
        else printf("f7(double)=%lf | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(date)=NULL | ");
        else printf("f8(date)=%02d-%02d-%02d | ", f8var.year(),f8var.month(),f8var.dayOfMonth());
	if(stmt->isFldNull(9)) printf("f9(time)=NULL | ");
        else printf("f9(time)=%02d:%02d:%02d | ", f9var.hours(),f9var.minutes(),f9var.seconds());
	if(stmt->isFldNull(10)) printf("f10(timestamp)=NULL | ");
        else printf("f10(timestamp)=%d-%d-%d %d:%d:%d | ", f10var.year(),f10var.month(),f10var.dayOfMonth(),f10var.hours(),f10var.minutes(),f10var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
      
//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 18; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 19; }
    printf("Table t1 dropped\n");
    strcpy(statement,"DROP TABLE t2;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 20; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 21; }
    printf("Table t2 dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

