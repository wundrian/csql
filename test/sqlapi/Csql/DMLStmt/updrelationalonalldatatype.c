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

  UPDATE t1 SET f1=10, f2=100, f3=1000, f4=10000, f5='CSQLMMDB', f6='LAKSHYA_BANGALORE', f7=100, f8=10000,f9='2009-01-10', f10='01:01:10', f11='2009-01-10 01:01:10' WHERE f1=1;
  UPDATE t1 SET f1=20, f2=200, f3=2000, f4=20000, f5='CSQLMMDB2', f6='LAKSHYA_BANGALORE2', f7=200, f8=20000,f9='2009-01-11', f10='01:01:11', f11='2009-01-11 01:01:11' WHERE f2=100;
  UPDATE t1 SET f1=30, f2=300, f3=3000, f4=30000, f5='CSQLMMDB3', f6='LAKSHYA_BANGALORE3', f7=300, f8=30000,f9='2009-01-12', f10='01:01:12', f11='2009-01-12 01:01:12' WHERE f3=2000;
  UPDATE t1 SET f1=40, f2=400, f3=4000, f4=40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=400, f8=40000,f9='2009-01-13', f10='01:01:13', f11='2009-01-13 01:01:13' WHERE f4=30000;
  UPDATE t1 SET f1=50, f2=500, f3=5000, f4=50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=500, f8=50000,f9='2009-01-14', f10='01:01:14', f11='2009-01-14 01:01:14' WHERE f5='CSQLMMDB4';
  UPDATE t1 SET f1=60, f2=600, f3=6000, f4=60000, f5='CSQLMMDB6', f6='LAKSHYA_BANGALORE6', f7=600, f8=60000,f9='2009-01-16', f10='01:01:16', f11='2009-01-16 01:01:16' WHERE f6='LAKSHYA_BANGALORE5';
  UPDATE t1 SET f1=70, f2=700, f3=7000, f4=70000, f5='CSQLMMDB7', f6='LAKSHYA_BANGALORE7', f7=700, f8=70000,f9='2009-01-17', f10='01:01:17', f11='2009-01-17 01:01:17' WHERE f7=600;
  UPDATE t1 SET f1=80, f2=800, f3=8000, f4=80000, f5='CSQLMMDB8', f6='LAKSHYA_BANGALORE8', f7=800, f8=80000,f9='2009-01-18', f10='01:01:18', f11='2009-01-18 01:01:18' WHERE f8=70000;
  UPDATE t1 SET f1=90, f2=900, f3=9000, f4=90000, f5='CSQLMMDB9', f6='LAKSHYA_BANGALORE9', f7=900, f8=90000,f9='2009-01-19', f10='01:01:19', f11='2009-01-19 01:01:19' WHERE f9='2009-01-18';
  UPDATE t1 SET f1=100, f2=1000, f3=10000, f4=100000, f5='CSQLMMDB10', f6='LAKSHYA_BANGALORE10', f7=1000, f8=100000,f9='2009-01-20', f10='01:01:20', f11='2009-01-20 01:01:20' WHERE f10='01:01:19';
  UPDATE t1 SET f1=110, f2=1100, f3=11000, f4=110000, f5='CSQLMMDB11', f6='LAKSHYA_BANGALORE11', f7=1100, f8=110000,f9='2009-09-09', f10='09:09:09', f11='2009-09-09 09:09:09' WHERE f11='2009-01-20 01:01:20';
  
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f1<3;
  UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2<3;
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f3<3;
  UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4<3;
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f5<'CSQL3';
  UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6<'LAKSHYA3';
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f7<3;
  UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8<3;
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f9<'2003/03/03';
  UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10<'03:03:03';
  UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f11<'2003/03/03 03:03:03';

  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f1<=4;
  UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f2<=4;
  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f3<=4;
  UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f4<=4;
  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f5<='CSQL4';
  UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f6<='LAKSHYA4';
  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f7<=4;
  UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f8<=4;
  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f9<='2004-04-04';
  UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f10<='04:04:04';
  UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f11<='2004-04-04 04:04:04';

  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f1!=7;  
  UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f2!=77;  
  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f3!=777;  
  UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f4!=7777;  
  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f5!='CSQL7';  
  UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f6!='LAKSHYA7';  
  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f7!=77.000000;  
  UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f8!=7777.000000;  
  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f9!='2007/7/7';  
  UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f10!='07:07:07';  
  UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f11!='2007/07/07 07:07:07';  
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
    printf("UPDATE t1 SET f1=10, f2=100, f3=1000, f4=10000, f5='CSQLMMDB', f6='LAKSHYA_BANGALORE', f7=100, f8=10000,f9='2009-01-10', f10='01:01:10', f11='2009-01-10 01:01:10' WHERE f1=1;\n");
    strcpy(statement,"UPDATE t1 SET f1=10, f2=100, f3=1000, f4=10000, f5='CSQLMMDB', f6='LAKSHYA_BANGALORE', f7=100, f8=10000,f9='2009-01-10', f10='01:01:10', f11='2009-01-10 01:01:10' WHERE f1=1;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=20, f2=200, f3=2000, f4=20000, f5='CSQLMMDB2', f6='LAKSHYA_BANGALORE2', f7=200, f8=20000,f9='2009-01-11', f10='01:01:11', f11='2009-01-11 01:01:11' WHERE f2=100;\n");
    strcpy(statement,"UPDATE t1 SET f1=20, f2=200, f3=2000, f4=20000, f5='CSQLMMDB2', f6='LAKSHYA_BANGALORE2', f7=200, f8=20000,f9='2009-01-11', f10='01:01:11', f11='2009-01-11 01:01:11' WHERE f2=100;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=30, f2=300, f3=3000, f4=30000, f5='CSQLMMDB3', f6='LAKSHYA_BANGALORE3', f7=300, f8=30000,f9='2009-01-12', f10='01:01:12', f11='2009-01-12 01:01:12' WHERE f3=2000;\n");
    strcpy(statement,"UPDATE t1 SET f1=30, f2=300, f3=3000, f4=30000, f5='CSQLMMDB3', f6='LAKSHYA_BANGALORE3', f7=300, f8=30000,f9='2009-01-12', f10='01:01:12', f11='2009-01-12 01:01:12' WHERE f3=2000;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=40, f2=400, f3=4000, f4=40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=400, f8=40000,f9='2009-01-13', f10='01:01:13', f11='2009-01-13 01:01:13' WHERE f4=30000;\n");
    strcpy(statement,"UPDATE t1 SET f1=40, f2=400, f3=4000, f4=40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=400, f8=40000,f9='2009-01-13', f10='01:01:13', f11='2009-01-13 01:01:13' WHERE f4=30000;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=50, f2=500, f3=5000, f4=50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=500, f8=50000,f9='2009-01-14', f10='01:01:14', f11='2009-01-14 01:01:14' WHERE f5='CSQLMMDB4';\n");
    strcpy(statement,"UPDATE t1 SET f1=50, f2=500, f3=5000, f4=50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=500, f8=50000,f9='2009-01-14', f10='01:01:14', f11='2009-01-14 01:01:14' WHERE f5='CSQLMMDB4';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=60, f2=600, f3=6000, f4=60000, f5='CSQLMMDB6', f6='LAKSHYA_BANGALORE6', f7=600, f8=60000,f9='2009-01-16', f10='01:01:16', f11='2009-01-16 01:01:16' WHERE f6='LAKSHYA_BANGALORE5';\n");
    strcpy(statement,"UPDATE t1 SET f1=60, f2=600, f3=6000, f4=60000, f5='CSQLMMDB6', f6='LAKSHYA_BANGALORE6', f7=600, f8=60000,f9='2009-01-16', f10='01:01:16', f11='2009-01-16 01:01:16' WHERE f6='LAKSHYA_BANGALORE5';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=700, f3=7000, f4=70000, f5='CSQLMMDB7', f6='LAKSHYA_BANGALORE7', f7=700, f8=70000,f9='2009-01-17', f10='01:01:17', f11='2009-01-17 01:01:17' WHERE f7=600;\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=700, f3=7000, f4=70000, f5='CSQLMMDB7', f6='LAKSHYA_BANGALORE7', f7=700, f8=70000,f9='2009-01-17', f10='01:01:17', f11='2009-01-17 01:01:17' WHERE f7=600;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=800, f3=8000, f4=80000, f5='CSQLMMDB8', f6='LAKSHYA_BANGALORE8', f7=800, f8=80000,f9='2009-01-18', f10='01:01:18', f11='2009-01-18 01:01:18' WHERE f8=70000;\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=800, f3=8000, f4=80000, f5='CSQLMMDB8', f6='LAKSHYA_BANGALORE8', f7=800, f8=80000,f9='2009-01-18', f10='01:01:18', f11='2009-01-18 01:01:18' WHERE f8=70000;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=90, f2=900, f3=9000, f4=90000, f5='CSQLMMDB9', f6='LAKSHYA_BANGALORE9', f7=900, f8=90000,f9='2009-01-19', f10='01:01:19', f11='2009-01-19 01:01:19' WHERE f9='2009-01-18';\n");
    strcpy(statement,"UPDATE t1 SET f1=90, f2=900, f3=9000, f4=90000, f5='CSQLMMDB9', f6='LAKSHYA_BANGALORE9', f7=900, f8=90000,f9='2009-01-19', f10='01:01:19', f11='2009-01-19 01:01:19' WHERE f9='2009-01-18';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=100, f2=1000, f3=10000, f4=100000, f5='CSQLMMDB10', f6='LAKSHYA_BANGALORE10', f7=1000, f8=100000,f9='2009-01-20', f10='01:01:20', f11='2009-01-20 01:01:20' WHERE f10='01:01:19';\n");
    strcpy(statement,"UPDATE t1 SET f1=100, f2=1000, f3=10000, f4=100000, f5='CSQLMMDB10', f6='LAKSHYA_BANGALORE10', f7=1000, f8=100000,f9='2009-01-20', f10='01:01:20', f11='2009-01-20 01:01:20' WHERE f10='01:01:19';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=110, f2=1100, f3=11000, f4=110000, f5='CSQLMMDB11', f6='LAKSHYA_BANGALORE11', f7=1100, f8=110000,f9='2009-09-09', f10='09:09:09', f11='2009-09-09 09:09:09' WHERE f11='2009-01-20 01:01:20';\n");
    strcpy(statement,"UPDATE t1 SET f1=110, f2=1100, f3=11000, f4=110000, f5='CSQLMMDB11', f6='LAKSHYA_BANGALORE11', f7=1100, f8=110000,f9='2009-09-09', f10='09:09:09', f11='2009-09-09 09:09:09' WHERE f11='2009-01-20 01:01:20';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    con->commit();
    stmt->free();

//Fetching records 
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
    count=0;
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

//Testing "<" operator
    printf("UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f1<3;\n");
    strcpy(statement,"UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f1<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);

    printf("UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2<3;\n");
    strcpy(statement,"UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f3<3;\n");
    strcpy(statement,"UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f3<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4<3;\n");
    strcpy(statement,"UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f5<'CSQL3';\n");
    strcpy(statement,"UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f5<'CSQL3';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6<'LAKSHYA3';\n");
    strcpy(statement,"UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6<'LAKSHYA3';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf(" UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f7<3;\n");
    strcpy(statement," UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f7<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8<3;\n");
    strcpy(statement,"UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8<3;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f9<'2003/03/03';\n");
    strcpy(statement,"UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f9<'2003/03/03';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10<'03:03:03';\n");
    strcpy(statement,"UPDATE t1 SET f1=2, f2=2, f3=2, f4=2, f5='CSQL2', f6='LAKSHYA2', f7=2, f8=2,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10<'03:03:03';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f11<'2003/03/03 03:03:03';\n");
    strcpy(statement,"UPDATE t1 SET f1=1, f2=1, f3=1, f4=1, f5='CSQL1', f6='LAKSHYA1', f7=1, f8=1,f9='2001-01-01', f10='01:01:01', f11='2001-01-01 01:01:01' WHERE f11<'2003/03/03 03:03:03';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);

//Fetching records 
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
    count=0;
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


//Testing "<=" operator
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f1<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f1<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f2<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f2<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f3<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f3<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f4<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f4<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f5<='CSQL4';\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f5<='CSQL4';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f6<='LAKSHYA4';\n");
    strcpy(statement,"UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f6<='LAKSHYA4';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f7<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f7<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f8<=4;\n");
    strcpy(statement,"UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f8<=4;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f9<='2004-04-04';\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f9<='2004-04-04';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f10<='04:04:04';\n");
    strcpy(statement,"UPDATE t1 SET f1=4, f2=4, f3=4, f4=4, f5='CSQL4', f6='LAKSHYA4', f7=4, f8=4,f9='2004-04-04', f10='04:04:04', f11='2004-04-04 04:04:04' WHERE f10<='04:04:04';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f11<='2004-04-04 04:04:04';\n");
    strcpy(statement,"UPDATE t1 SET f1=3, f2=3, f3=3, f4=3, f5='CSQL3', f6='LAKSHYA3', f7=3, f8=3,f9='2003-03-03', f10='03:03:03', f11='2003-03-03 03:03:03' WHERE f11<='2004-04-04 04:04:04';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);

//Fetching records
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
    count=0;
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

//Testing "!=" operator
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f1!=7;\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f1!=7;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f2!=77\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f2!=77");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f3!=777;\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f3!=777;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f4!=7777;\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f4!=7777;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f5!='CSQL7';\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f5!='CSQL7';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f6!='LAKSHYA7';\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f6!='LAKSHYA7';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f7!=77.000000;\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f7!=77.000000;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f8!=7777.000000;\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f8!=7777.000000;");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f9!='2007/7/7';\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f9!='2007/7/7';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f10!='07:07:07';\n");
    strcpy(statement,"UPDATE t1 SET f1=80, f2=80, f3=80, f4=80, f5='CSQL80', f6='LAKSHYA80', f7=80, f8=80,f9='2080-08-08', f10='08:08:08', f11='2080-08-08 08:08:08' WHERE f10!='07:07:07';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);
    printf("UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f11!='2007/07/07 07:07:07';\n");
    strcpy(statement,"UPDATE t1 SET f1=70, f2=70, f3=70, f4=70, f5='CSQL70', f6='LAKSHYA70', f7=70, f8=70,f9='2070-07-07', f10='07:07:07', f11='2070-07-07 07:07:07' WHERE f11!='2007/07/07 07:07:07';");
    rv = stmt->prepare(statement);
    rv = stmt->execute(rows);

//Fetching records
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
    count=0;
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

//Droping table
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

