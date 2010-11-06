/*  create table T1 with 10 fields.
 *  insert some records into it.
 *  update T1 with some Null values in the parameter.
    noOfParamFields() should return 8.   
 *  select * from T1;
 
 *  Author : Jitendra Lenka.
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();  
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
    if(rv!=OK) { delete stmt; delete con; return 1; }
    stmt->free();
    printf("Table created\n");
    // insert into table
    strcpy(statement,"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    int f1var = 0;
    short int f2var = 10;
    char f3var[32]="jitendra";
    float f4var = 5.5;
    float f5var = 10.50;
    Date f6var;
    f6var.set(2008,01,21);
    Time f7var;
    f7var.set(12,29,30);     
    TimeStamp f8var;
    f8var.setDate(2008,01,21);
    f8var.setTime(12,29,30);
    int f9var = 20;
    long long f10var = 12000;
    char f11var[8]="23fe";
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    int count=0;
    for(int i=0;i<10;i++) {	
        rv  = con->beginTrans();
	    if(rv!=OK) break;
	    f1var=i;
        f2var++;
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
        stmt->setBinaryParam(11,f11var,8);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
    	rv = con->commit();
	    if(rv!=OK)break;
        count++;
    }
    printf("%d Rows inserted \n",count);
    stmt->free();
    //**********************************************************
    // UPDATE TABLE
    strcpy(statement,"UPDATE T1 SET F10=?,F8=?,F6=?,F5=?,F4=?,F3=?,F11=? WHERE F2=?;");
    rv = stmt->prepare(statement);
    int nop;
    nop = stmt->noOfParamFields();
    printf("noOfParamFields return=%d\n",nop);
    if(nop!=8)return 1;
    long long f10var1=15000;
    TimeStamp f8var1;
    f8var1.setDate(2007,3,30);
    f8var1.setTime(10,25,55);
    Date f6var1;
    f6var1.set(2007,3,30);
    float f5var1=20.25;
    float f4var1=11.22;
    char f3var1[10]="lakshya";
    char f11var1[8]="ab12";
    short int f2var1=10;
    count=0;
    for(int i=0;i<5;i++) {
        rv = con->beginTrans();
        if(rv!=OK)break;
        f2var1++;
        stmt->setShortParam(8,f2var1);
        stmt->setLongLongParam(1,f10var1);
        stmt->setTimeStampParam(2,f8var1);
        stmt->setNull(3);
        stmt->setFloatParam(4,f5var1);
        stmt->setFloatParam(5,f4var1);
        stmt->setNull(6);
        stmt->setBinaryParam(7,f11var1, 8);
        //stmt->setShortParam(7,f2var1);
        rv = stmt->execute(rows);
        if(rv!=OK)break;
        rv  = con->commit();
        if(rv!=OK)break;
        count++;
    }
    stmt->free();
    printf("%d Rows updated\n",count);
    //**********************************************************
    // SELECT * FROM T1;
    strcpy(statement,"SELECT * FROM T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 5; }
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
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 6;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
        if(stmt->isFldNull(1)) printf("F1=NULL | ");
        else printf("F1=%d | ", f1var);
        if(stmt->isFldNull(2)) printf("F2=NULL | ");
        else printf("F2=%hd | ", f2var);
        if(stmt->isFldNull(3)) printf("F3=NULL | ");
        else printf("F3=%s | ", f3var);
        if(stmt->isFldNull(4)) printf("F4=NULL | ");
        else printf("F4=%f | ", f4var);
        if(stmt->isFldNull(5)) printf("F5=NULL | ");
        else printf("F5=%f | ", f5var);
        if(stmt->isFldNull(6)) printf("F6=NULL | ");
        else printf("F6=%02d-%02d-%02d | ",f6var.year(), f6var.month(), f6var.dayOfMonth());
        if(stmt->isFldNull(7)) printf("F7=NULL | ");
        else printf("F7=%02d:%02d:%02d | ", f7var.hours(),f7var.minutes(),f7var.seconds());
        if(stmt->isFldNull(8)) printf("F8=NULL | ");
        else printf("F8=%d-%d-%d %d:%d:%d | ", f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds());
        if(stmt->isFldNull(9)) printf("F9=NULL | ");
        else printf("F9=%d | ", f9var);
        if(stmt->isFldNull(10)) printf("F10=NULL | ");
        else printf("F10=%lld | ", f10var);
        if(stmt->isFldNull(11)) printf("F11=NULL | ");
        else { AllDataType::printVal(f11var,typeBinary,4);
        }
        printf("\n");
        count++;
    }
/*
        if(f1var==5)printf("\n");
        if(stmt->isFldNull(1))
                printf("f1=null ");
        if(stmt->isFldNull(2))
                printf("f2=null ");
        if(stmt->isFldNull(3))
                printf("f3=null ");
        if(stmt->isFldNull(4))
                printf("f4=null ");
        if(stmt->isFldNull(5))
                printf("f5=null ");
        if(stmt->isFldNull(6))
                printf("f6=null ");
        if(stmt->isFldNull(7))
                printf("f7=null ");
        if(stmt->isFldNull(8))
                printf("f8=null ");
        if(stmt->isFldNull(9))
                printf("f9=null ");
        if(stmt->isFldNull(10))
                printf("f10=null ");
        if(stmt->isFldNull(11))
                printf("f11=null \n");

       printf("\n");

        printf("F1=%d | F2=%hd | F3=%s | F4=%f | F5=%f | DATE=%d-%d-%d | TIME=%d:%d:%d | TIMESTAMP=%d-%d-%d %d:%d:%d | F9=%d | F10=%lld",f1var,f2var,f3var,f4var,f5var,f6var.year(),f6var.month(),f6var.dayOfMonth(),f7var.hours(),f7var.minutes(),f7var.seconds(),f8var.year(),f8var.month(),f8var.dayOfMonth(),f8var.hours(),f8var.minutes(),f8var.seconds(),f9var,f10var);
        printf(" | ");
        AllDataType::printVal(f11var,typeBinary,4);
        printf("\n");
        count++;
    }*/
    stmt->close();
    rv = con->commit();
    if(rv !=OK) { delete stmt; delete con; return 7; }
    printf("%d Rows fetched\n",count);
    stmt->free();
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 9; }
    printf("Table dropped\n");
    stmt->free(); delete stmt; delete con; 
    return 0;
} 	 	      
