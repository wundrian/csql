/*
  Aggregate test 
  CREATE TABLE t1(f1 INT,f2 BIGINT,f3 DOUBLE,f4 DATE);
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(100,100,100,'2009-11-23');
  INSERT INTO t1 VALUES(200,200,200,'2009-11-25');
  INSERT INTO t1 VALUES(100,300,300,'2009-11-27');
  INSERT INTO t1 VALUES(200,400,400,'2009-11-29'); 
  INSERT INTO t1 VALUES(300,500,500,'2009-12-01');
  SELECT * FROM t1;
  select count(f4) from t1;
  select f1, sum(f2), avg(f3), max(f4) from t1 group by f1; 
  select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having max(f4)>'2009/11/29';
  select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having (max(f4) >'2009/11/26' and max(f4) < '2009-11-28') or avg(f3) > 400;
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
    printf("CREATE TABLE t1(f1 INT,f2 BIGINT,f3 DOUBLE,f4 DATE);\n");
    strcpy(statement,"CREATE TABLE t1(f1 INT,f2 BIGINT,f3 DOUBLE,f4 DATE);");
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
    printf("INSERT INTO t1 VALUES(100,100,100,'2009-11-23');\n");
    stmt->prepare("INSERT INTO t1 VALUES(100,100,100,'2009-11-23');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(200,200,200,'2009-11-25');\n");
    stmt->prepare("INSERT INTO t1 VALUES(200,200,200,'2009-11-25');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(100,300,300,'2009-11-27');\n");
    stmt->prepare("INSERT INTO t1 VALUES(100,300,300,'2009-11-27');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(200,400,400,'2009-11-29');\n");
    stmt->prepare("INSERT INTO t1 VALUES(200,400,400,'2009-11-29');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(300,500,500,'2009-12-01');\n");
    stmt->prepare("INSERT INTO t1 VALUES(300,500,500,'2009-12-01');");
    stmt->execute(rows);
    con->commit();
    stmt->free();

    int f1var;
    long long f2var;
    double f3var;
    Date f4var;
    
//Fetching records after insert
    printf("SELECT * FROM t1;\n");
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
	if(stmt->isFldNull(1)) printf("f1(int)=NULL | ");
        else printf("f1(int)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(bigint)=NULL | ");
        else printf("f2(bigint)=%lld | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(double)=NULL | ");
        else printf("f3(double)=%lf | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(date)=NULL | ");
        else printf("f4(date)=%d-%d-%d | ", f4var.year(),f4var.month(),f4var.dayOfMonth());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);

//select count(f4) from t1;    
    int cnt=0;
    strcpy(statement,"SELECT count(f4) FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 7; }
    stmt->bindField(1,&cnt);
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	printf("select count(f4) from t1 = %d\n",cnt);
    }
    stmt->free();
    rv = con->commit();    

//select f1, sum(f2), avg(f3), max(f4) from t1 group by f1;
   long long sum = 0;
   double avg = 0;
   Date max;
   strcpy(statement,"select f1, sum(f2), avg(f3), max(f4) from t1 group by f1;");    
   rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&sum);
    stmt->bindField(3,&avg);
    stmt->bindField(4,&max);
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    printf("\nselect f1, sum(f2), avg(f3), max(f4) from t1 group by f1;\n");
    while(stmt->fetch() !=NULL) {
        printf("f1=%d | ", f1var);
        printf("sum(f2)=%lld | ", sum);
        printf("avg(f3)=%lf | ", avg);
        printf("max(f4)=%d-%d-%d | ", max.year(),max.month(),max.dayOfMonth());
        printf("\n");
    }
    stmt->close();
    rv = con->commit();

//select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having max(f4)>'2009/11/29';
   strcpy(statement,"select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having max(f4)>'2009/11/29';");    
   rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&sum);
    stmt->bindField(3,&avg);
    stmt->bindField(4,&max);
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    printf("\nselect f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having max(f4)>'2009/11/29';\n");
    while(stmt->fetch() !=NULL) {
        printf("f1=%d | ", f1var);
        printf("sum(f2)=%lld | ", sum);
        printf("avg(f3)=%lf | ", avg);
        printf("max(f4)=%d-%d-%d | ", max.year(),max.month(),max.dayOfMonth());
        printf("\n");
    }
    stmt->close();
    rv = con->commit();

//select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having (max(f4) >'2009/11/26' and max(f4) < '2009-11-28') or avg(f3) > 400;
   strcpy(statement,"select f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having (max(f4) >'2009/11/26' and max(f4) < '2009-11-28') or avg(f3) > 400;");    
   rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&sum);
    stmt->bindField(3,&avg);
    stmt->bindField(4,&max);
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    printf("\nselect f1, sum(f2), avg(f3), max(f4) from t1 group by f1 having (max(f4) >'2009/11/26' and max(f4) < '2009-11-28') or avg(f3) > 400;\n");
    while(stmt->fetch() !=NULL) {
        printf("f1=%d | ", f1var);
        printf("sum(f2)=%lld | ", sum);
        printf("avg(f3)=%lf | ", avg);
        printf("max(f4)=%d-%d-%d | ", max.year(),max.month(),max.dayOfMonth());
        printf("\n");
    }
    stmt->close();
    rv = con->commit();

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

