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
    stmt->close();
    rv = con->commit();
    if(rv !=OK) { delete stmt; delete con; return 7; }
    printf("Total row fetched=%d\n",count);
    stmt->free();
   //=================================
   // Select with projected values
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
