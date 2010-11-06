/*
  Test Update conditionally using relational operators on all datatypes.
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2','LAKSHYA2',22.00,2222.00,'2002-02-02','02:02:02','2002-02-02 02:02:02');
  INSERT INTO t1 VALUES(3,33,333,3333,'CSQL3','LAKSHYA3',33.00,3333.00,'2003-03-03','03:03:03','2003-03-03 03:03:03');
  INSERT INTO t1 VALUES(4,44,444,4444,'CSQL4','LAKSHYA4',44.00,4444.00,'2004-04-04','04:04:04','2004-04-04 04:04:04');
  INSERT INTO t1 VALUES(5,55,555,5555,'CSQL5','LAKSHYA5',55.00,5555.00,'2005-05-05','05:05:05','2005-05-05 05:05:05');
  INSERT INTO t1 VALUES(6,66,666,6666,'CSQL6','LAKSHYA6',66.00,6666.00,'2006-06-06','06:06:06','2006-06-06 06:06:06');
  INSERT INTO t1 VALUES(7,77,777,7777,'CSQL7','LAKSHYA7',77.00,7777.00,'2007-07-07','07:07:07','2007-07-07 07:07:07');
  INSERT INTO t1 VALUES(8,88,888,8888,'CSQL8','LAKSHYA8',88.00,8888.00,'2008-08-08','08:08:08','2008-08-08 08:08:08');
  INSERT INTO t1 VALUES(9,99,999,9999,'CSQL9','LAKSHYA9',99.00,9999.00,'2009-09-09','09:09:09','2009-09-09 09:09:09');
  INSERT INTO t1 VALUES(10,100,1000,10000,'CSQL10',NULL,100.00,10000.00,'2010-10-10','10:10:10','2010-10-10 10:10:10');

  DELETE FROM t1 WHERE f3=111;
  DELETE FROM t1 WHERE f4<3333;
  DELETE FROM t1 WHERE f6<='LAKSHYA3';
  DELETE FROM t1 WHERE f9>'2008-08-08' and f10 <'10:10:10';
  
  DELETE FROM t1 WHERE f3 between 100 and 500;
  DELETE FROM t1 WHERE f6 like '%AKSHYA5';
  DELETE FROM t1 WHERE f11 in ('2005-05-05 05:05:05','2006-06-06 06:06:06');

  DELETE FROM t1 WHERE f3 is NOT NULL and f4=7777;

  DELETE FROM t1 WHERE f6 is NULL or not(f4=8888);

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
    printf("CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);");
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
    stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2','LAKSHYA2',22.00,2222.00,'2002-02-02','02:02:02','2002-02-02 02:02:02');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(3,33,333,3333,'CSQL3','LAKSHYA3',33.00,3333.00,'2003-03-03','03:03:03','2003-03-03 03:03:03');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(4,44,444,4444,'CSQL4','LAKSHYA4',44.00,4444.00,'2004-04-04','04:04:04','2004-04-04 04:04:04');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(5,55,555,5555,'CSQL5','LAKSHYA5',55.00,5555.00,'2005-05-05','05:05:05','2005-05-05 05:05:05');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(6,66,666,6666,'CSQL6','LAKSHYA6',66.00,6666.00,'2006-06-06','06:06:06','2006-06-06 06:06:06');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(7,77,777,7777,'CSQL7','LAKSHYA7',77.00,7777.00,'2007-07-07','07:07:07','2007-07-07 07:07:07');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(8,88,888,8888,'CSQL8','LAKSHYA8',88.00,8888.00,'2008-08-08','08:08:08','2008-08-08 08:08:08');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(9,99,999,9999,'CSQL9','LAKSHYA9',99.00,9999.00,'2009-09-09','09:09:09','2009-09-09 09:09:09');");
    stmt->execute(rows);
    rows=0;
    stmt->prepare("INSERT INTO t1 VALUES(10,100,1000,10000,'CSQL10',NULL,100.00,10000.00,'2010-10-10','10:10:10','2010-10-10 10:10:10');");
    stmt->execute(rows);
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
    printf("SELECT * FROM t1;\n");
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 6; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 7;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1=NULL | ");
        else printf("f1=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(=NULL | ");
        else printf("f2(=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3=NULL | ");
        else printf("f3=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4=NULL | ");
        else printf("f4=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5=NULL | ");
        else printf("f5=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6=NULL | ");
        else printf("f6=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7=NULL | ");
        else printf("f7=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8=NULL | ");
        else printf("f8=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9=NULL | ");
        else printf("f9=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10=NULL | ");
        else printf("f10=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11=NULL | ");
        else printf("f11=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
      
//Updating records.
    con->beginTrans();
    printf("DELETE FROM t1 WHERE f3=111;\n");
    strcpy(statement,"DELETE FROM t1 WHERE f3=111;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f4<3333;\n");
    strcpy(statement,"DELETE FROM t1 WHERE f4<3333;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f6<='LAKSHYA3';\n");
    strcpy(statement,"DELETE FROM t1 WHERE f6<='LAKSHYA3';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f9>'2008-08-08' and f10 <'10:10:10';\n");
    strcpy(statement,"DELETE FROM t1 WHERE f9>'2008-08-08' and f10 <'10:10:10';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f3 between 100 and 500;\n");
    strcpy(statement,"DELETE FROM t1 WHERE f3 between 100 and 500;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f6 like '%AKSHYA5';\n");
    strcpy(statement,"DELETE FROM t1 WHERE f6 like '%AKSHYA5';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f11 in ('2005-05-05 05:05:05','2006-06-06 06:06:06');\n");
    strcpy(statement,"DELETE FROM t1 WHERE f11 in ('2005-05-05 05:05:05','2006-06-06 06:06:06');");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f3 is NOT NULL and f4=7777;\n");
    strcpy(statement,"DELETE FROM t1 WHERE f3 is NOT NULL and f4=7777;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("DELETE FROM t1 WHERE f6 is NULL or not(f4=8888);\n");
    strcpy(statement,"DELETE FROM t1 WHERE f6 is NULL or not(f4=8888);");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    stmt->free();
    rv = con->commit();    

//Fetching records 
    printf("SELECT * FROM t1;\n");
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 9;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1=NULL | ");
        else printf("f1=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(=NULL | ");
        else printf("f2(=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3=NULL | ");
        else printf("f3=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4=NULL | ");
        else printf("f4=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5=NULL | ");
        else printf("f5=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6=NULL | ");
        else printf("f6=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7=NULL | ");
        else printf("f7=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8=NULL | ");
        else printf("f8=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9=NULL | ");
        else printf("f9=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10=NULL | ");
        else printf("f10=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11=NULL | ");
        else printf("f11=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);

//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

