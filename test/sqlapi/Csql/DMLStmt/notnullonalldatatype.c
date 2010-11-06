/*
 NOT NULL Constraint Testing with all datatypes. 
 CREATE TABLE t1(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL);
 Try to put null values in Not Null fields,it should not be allowed
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
    printf("REATE TABLE t1(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL);");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL);");
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
    printf("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');\n");
    rv = stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    if(rv!=OK) { 
	stmt->prepare("DROP TABLE t1;");
	stmt->execute(rows);
	if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 6;
    }
    rv = stmt->execute(rows);
    if(rv!=OK) {
        stmt->prepare("DROP TABLE t1;");
        stmt->execute(rows);
        if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
        return 7;
    }
    
    printf("INSERT INTO t1 VALUES(2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\n");
    rv = stmt->prepare("INSERT INTO t1 VALUES(2,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);");
    if(rv!=OK) { 
	stmt->prepare("DROP TABLE t1;");
	stmt->execute(rows);
	if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 8;
    }
    rv = stmt->execute(rows);
    if(rv==OK) {
        stmt->prepare("DROP TABLE t1;");
        stmt->execute(rows);
        if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
        return 9;
    }
    
    printf("INSERT INTO t1 VALUES(NULL,33,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);\n");
    rv = stmt->prepare("INSERT INTO t1 VALUES(NULL,33,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);");
    if(rv!=OK) { 
	stmt->prepare("DROP TABLE t1;");
	stmt->execute(rows);
	if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 10;
    }
    rv = stmt->execute(rows);
    if(rv==OK) {
        stmt->prepare("DROP TABLE t1;");
        stmt->execute(rows);
        if(rv==OK) { printf("Table Dropped successfully\n"); }
        stmt->free(); con->disconnect(); delete stmt; delete con;
        return 11;
    }
    
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
    if(rv!=OK) { delete stmt; delete con; return 12; }
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
//Updating records
    printf("UPDATE t1 SET f1=NULL WHERE f1=1;\n");
    rv = stmt->prepare("UPDATE t1 SET f1=null WHERE f1=1;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 14;
    }
    
    printf("UPDATE t1 SET f2=NULL WHERE f1=11;\n");
    rv = stmt->prepare("UPDATE t1 SET f2=NULL WHERE f1=11;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 15;
    }
    
    printf("UPDATE t1 SET f3=NULL WHERE f3=111;\n");
    rv = stmt->prepare("UPDATE t1 SET f3=NULL WHERE f1=111;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 16;
    }
    
    printf("UPDATE t1 SET f4=NULL WHERE f3=1111;\n");
    rv = stmt->prepare("UPDATE t1 SET f4=NULL WHERE f4=1111;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 17;
    }
    
    printf("UPDATE t1 SET f5=NULL WHERE f5='CSQL1';\n");
    rv = stmt->prepare("UPDATE t1 SET f5=NULL WHERE f5='CSQL1';");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 18;
    }
    
    printf("UPDATE t1 SET f6=NULL WHERE f6='LAKSHYA1';\n");
    rv = stmt->prepare("UPDATE t1 SET f6=NULL WHERE f6='LAKSHYA1';");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 19;
    }
    
    printf("UPDATE t1 SET f7=NULL WHERE f7=11;\n");
    rv = stmt->prepare("UPDATE t1 SET f7=NULL WHERE f7=11;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 20;
    }
    
    printf("UPDATE t1 SET f8=NULL WHERE f8=1111;\n");
    rv = stmt->prepare("UPDATE t1 SET f8=NULL WHERE f8=1111;");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 21;
    }
    
    printf("UPDATE t1 SET f9=NULL WHERE f9='2001-01-01';\n");
    rv = stmt->prepare("UPDATE t1 SET f9=NULL WHERE f9='2001-01-01';");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 22;
    }
    
    printf("UPDATE t1 SET f10=NULL WHERE f10='01:01:01';\n");
    rv = stmt->prepare("UPDATE t1 SET f10=NULL WHERE f10='01:01:01';");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 23;
    }
    
    printf("UPDATE t1 SET f11=NULL WHERE f11='2001-01-01 01:01:01';\n");
    rv = stmt->prepare("UPDATE t1 SET f11=NULL WHERE f11='2001-01-01 01:01:01';");
    if(rv==OK) { 
	stmt->prepare("DROP TABLE t1;"); 
	stmt->execute(rows); 
	if(rv==OK)  printf("Table Dropped successfully\n"); 
        stmt->free(); con->disconnect(); delete stmt; delete con;
	return 24;
    }
    
//Fetching records after Update
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 25; }
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
    if(rv!=OK)return 26;
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
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 27; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 28; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

