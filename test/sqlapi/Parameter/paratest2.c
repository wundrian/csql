/*  create table T1 with 10 fields.
 *  insert some records into it.
 *  select * from T1 with where clause;
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con= createConnection();
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 INT,F10 BIGINT, F11 BINARY(4));");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    stmt->free();
    printf("Table created\n");
    // insert into table
    strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    int f1var = 100;
    short int f2var = 10;
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
    char f11var[8]="23fe";
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    int count=0;
    for(int i=0;i<10;i++) {	
	    rv = con->beginTrans();
	    if (rv!=OK) break;
        stmt->setIntParam(1,f1var);
        stmt->setShortParam(2,f2var);
        stmt->setStringParam(3,f3var);
        stmt->setFloatParam(4,f4var);
        stmt->setFloatParam(5,f5var);
        stmt->setDateParam(6,f6var);
        stmt->setTimeParam(7,f7var);
        stmt->setTimeStampParam(8,f8var);
        stmt->setIntParam(9,f9var);
        stmt->setLongLongParam(10,f10var);
        stmt->setBinaryParam(11,f11var, 4);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
    	rv = con->commit();
	    if (rv != OK) break;
        count++;
    }
    printf("Total rows inserted %d\n",count);
    stmt->free();
    //**********************************************************
    // SELECT * FROM T1;
    strcpy(statement,"SELECT * FROM T1 WHERE F1=? AND F2=? AND F3=? AND F4=? AND F5=? AND F6=? AND F7=? AND F8=? AND F9=? AND F10=? AND F11=?;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,&f5var);
    stmt->bindField(6,&f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,f11var);
    int f1var1=100;
    short int f2var1=10;
    char f3var1[20]="jitendra";
    float f4var1=5.5;
    float f5var1=10.50;
    Date f6var1;
    f6var1.set(2007,1,21);
    Time f7var1;
    f7var1.set(12,29,30);
    TimeStamp f8var1;
    f8var1.setDate(2007,1,21);
    f8var1.setTime(12,29,30);
    int f9var1=20;
    long long f10var1=12000; 
    char f11var1[8]="23fe";
    count=0;
    rv  = con->beginTrans();
    if(rv!=OK)return 5;
    stmt->setIntParam(1,f1var1);
    stmt->setShortParam(2,f2var1);
    stmt->setStringParam(3,f3var1);
    stmt->setFloatParam(4,f4var1);
    stmt->setFloatParam(5,f5var1);
    stmt->setDateParam(6,f6var1);
    stmt->setTimeParam(7,f7var1);
    stmt->setTimeStampParam(8,f8var1);
    stmt->setIntParam(9,f9var1);
    stmt->setLongLongParam(10,f10var1);
    stmt->setBinaryParam(11,f11var1, 4);
    stmt->execute(rows);
    while(stmt->fetch()!=NULL) {
        printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
        printf(" | ");
        AllDataType::printVal(f11var,typeBinary,4);
        printf("\n");
        count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv!=OK)return 6;
    stmt->free();
    printf("%d Tuples fetched\n",count);
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK){delete stmt; delete con; return -1;}
    rv = stmt->execute(rows);
    if(rv!=OK){delete stmt;delete con;return -1;}
    printf("Table dropped\n");
    stmt->free(); delete stmt; delete con;
    return 0;
}
