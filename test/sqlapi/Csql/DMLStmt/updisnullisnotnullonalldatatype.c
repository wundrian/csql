/*
  Testing update on all datatypes using is null and is not null  operators
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  INSERT INTO t1 VALUES(NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f1 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f1 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f2 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f3 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f3 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f4 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f5 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f5 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f6 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f7 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f7 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f8 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f9 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f9 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f10 IS NOT NULL;
  UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f11 IS NULL;
  UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f11 IS NOT NULL;
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
    
//Fetching records after Insert
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
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);

//Inserting Records
    con->beginTrans();
    rows=0;
    printf("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');\n");
    stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("INSERT INTO t1 VALUES(NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\n");
    stmt->prepare("INSERT INTO t1 VALUES(NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f1 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f1 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f1 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f1 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f2 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f3 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f3 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f4 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f4 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f4 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f5 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f5 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f5 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f5 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f6 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f6 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f6 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f7 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f7 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f7 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f7 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f8 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f8 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f8 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f9 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f9 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f9 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f9 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f10 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f10 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f10 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f11 IS NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=2, f2=22, f3=222, f4=2222, f5='CSQL2', f6='LAKSHYA2', f7=22.00, f8=2222.00,f9='2002-02-02', f10='02:02:02', f11='2002-02-02 02:02:02' WHERE f11 IS NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    printf("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f11 IS NOT NULL;\n");
    stmt->prepare("UPDATE t1 SET f1=NULL, f2=NULL, f3=NULL, f4=NULL, f5=NULL, f6=NULL, f7=NULL, f8=NULL,f9=NULL, f10=NULL, f11=NULL WHERE f11 IS NOT NULL;");
    stmt->execute(rows);
    con->commit();
    stmt->free();

//Fetching records after update
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
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
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

