/*  create table T1 with 10 fields.
 *  insert some records into it with null values
 * 
 *  
 *  select * from T1;
 
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con =  createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 INT,F10 BIGINT, F11 BINARY(4));");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    stmt->free();
    printf("Table T1 created\n");
    // insert into table
    strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    int f1var = 0;
    short int f2var = 1;
    char f3var[32]="jitendra";
    float f4var = 5.5;
    float f5var = 10.50;
    Date f6var;
    f6var.set(2007,01,21);
    Time f7var;
    f7var.set(12,29,30);     
    TimeStamp f8var;
    f8var.setDate(2007,01,21);
    f8var.setTime(12,29,30);
    int f9var = 20;
    long long f10var = 12000;
    char f11var[12]="23fe";
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    int count=0;
    for(int i=0;i<10;i++) {	
	    rv  = con->beginTrans();
	    if(rv!=OK) break;
	    f1var=i;
        stmt->setIntParam(1,f1var);
        stmt->setShortParam(2,f2var);
        stmt->setStringParam(3,f3var);
        stmt->setFloatParam(4,f4var);
        stmt->setNull(5);
        stmt->setDateParam(6,f6var);
        stmt->setNull(7);
        stmt->setTimeStampParam(8,f8var);
        stmt->setIntParam(9,f9var);
        stmt->setLongLongParam(10,f10var);
        stmt->setBinaryParam(11,f11var, 12);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
    	rv = con->commit();
        if(rv!=OK)break;
        count++;
    }
    stmt->free();
    //*********************************************************
    //  Insert with value list records from the T1
    strcpy(statement,"INSERT INTO T1(F1,F2,F3,F4,F5,F6,F7,F8,F9,F10) VALUES(?,?,?,?,?,?,?,?,?,?);");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    for(int i=0;i<10;i++) {
            rv  = con->beginTrans();
            if(rv!=OK) break;
            f1var=i;
        stmt->setNull(1);
        stmt->setShortParam(2,f2var);
        stmt->setStringParam(3,f3var);
        stmt->setFloatParam(4,f4var);
        stmt->setNull(5);
        stmt->setDateParam(6,f6var);
        stmt->setNull(7);
        stmt->setTimeStampParam(8,f8var);
        stmt->setIntParam(9,f9var);
        stmt->setLongLongParam(10,f10var);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
        rv = con->commit();
        if(rv!=OK)break;
        count++;
    }
    printf("Total rows inserted %d\n",count);
    stmt->free();
    int cnt = 0;
    int max = 0;
    int min = 0;
    double avg = 0;
    long long sum = 0;
    //**********************************************************
    // SELECT * FROM T1;
    strcpy(statement,"SELECT count(F1), MAX(F1), MIN(F2), avg(F9), sum(F10) FROM T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    stmt->bindField(1,&cnt);
    stmt->bindField(2,&max);
    stmt->bindField(3,&min);
    stmt->bindField(4,&avg);
    stmt->bindField(5,&sum);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
        printf("select count(*) from T1 = %d\n", cnt);
        printf("select max(F1) from T1 = %d\n", max);
        printf("select min(F2) from T1 = %d\n", min);
        printf("select avg(F9) from T1 = %lf\n", avg);
        printf("select sum(F10) from T1 = %d\n", sum);
        count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv !=OK) { delete stmt; delete con; return 7; }
    printf("Total row fetched=%d\n",count);
    stmt->free();
   strcpy(statement,"SELECT F1,F2,F3,F4,F5 FROM T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,&f5var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
        if(stmt->isFldNull("F1")) printf("F1=NULL | ");
        else printf("F1=%d | ", f1var);
        if(stmt->isFldNull("F2")) printf("F2=NULL | ");
        else printf("F2=%hd | ", f2var);
        if(stmt->isFldNull("F3")) printf("F3=NULL | ");
        else printf("F3=%s | ", f3var);
        if(stmt->isFldNull("F4")) printf("F4=NULL | ");
        else printf("F4=%f | ", f4var);
        if(stmt->isFldNull("F5")) printf("F5=NULL | ");
        else printf("F5=%f | ", f5var);
        printf("\n");
        count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv !=OK) { delete stmt; delete con; return 7; }
    printf("Total row fetched=%d\n",count);
    stmt->free();
//==========================

    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 9; }
    printf("Table dropped\n");
    stmt->free(); delete stmt; delete con;
    return 0;
} 	 	      
