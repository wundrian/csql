/* select tuple with WHERE clause having param for some fields
 Create a table having f1 date, f2 tnt and f3 string
 Insert 5-6 records
 Execute SELECT * FROM T1 WHERE f1='Date Value' AND f2=? AND f3=?; 
 Author : Nihar Paital.
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
    strcpy(statement,"CREATE TABLE T1(F1 DATE,F2 INT,F3 CHAR(10));");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    stmt->free();
    printf("Table created\n");
    con->beginTrans();
    stmt->prepare("INSERT INTO T1 values('2008-10-21',0,'Nihar0');");
    stmt->execute(rows);
    stmt->prepare("INSERT INTO T1 values('2009-11-10',1,'Nihar1');");
    stmt->execute(rows);
    stmt->prepare("INSERT INTO T1 values('2008-10-24',2,'Nihar2');");
    stmt->execute(rows);
    stmt->prepare("INSERT INTO T1 values('2009-11-10',3,'Nihar3');");
    stmt->execute(rows);
    stmt->prepare("INSERT INTO T1 values('2008-10-21',4,'Nihar4');");
    stmt->execute(rows);
    stmt->prepare("INSERT INTO T1 values('2009-11-10',5,'Nihar5');");
    stmt->execute(rows);
    con->commit();
    stmt->free();
    //**********************************************************
    // SELECT * FROM T1;
    Date f1var;
    f1var.set(2001,01,01);
    int f2var=0;
    char f3var[32]="CSQL";
    printf("SELECT * FROM T1;\n");
    strcpy(statement,"SELECT * FROM T1;");
    stmt->prepare(statement);
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    int count=0;
    con->beginTrans();
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
       printf("F1=%02d-%02d-%02d | F2=%d | F3=%s",f1var.year(), f1var.month(), f1var.dayOfMonth(), f2var,f3var);
        printf("\n");
        count++;
    }
    stmt->close();
    con->commit();
    printf("%d Rows fetched\n",count);
    stmt->free();
    
    printf("SELECT * FROM T1 WHERE F1='2009-11-10';\n");
    strcpy(statement,"SELECT * FROM T1 WHERE F1='2009-11-10';");
    stmt->prepare(statement);
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    count=0;
    con->beginTrans();
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
       printf("F1=%02d-%02d-%02d | F2=%d | F3=%s",f1var.year(), f1var.month(), f1var.dayOfMonth(), f2var,f3var);
        printf("\n");
        count++;
    }
    stmt->close();
    con->commit();
    printf("%d Rows fetched\n",count);
    stmt->free();
   
    printf("SELECT * FROM T1 where F2 >= ? and F3 <= ?;\n");
    strcpy(statement,"SELECT * FROM T1 where F2 >= ? and F3 <= ?;");
    stmt->prepare(statement);
    f2var=1;
    strcpy(f3var,"Nihar3");
    stmt->setIntParam(1,f2var);
    stmt->setStringParam(2,f3var);
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    count=0;
    con->beginTrans();
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
       printf("F1=%02d-%02d-%02d | F2=%d | F3=%s",f1var.year(), f1var.month(), f1var.dayOfMonth(), f2var,f3var);
        printf("\n");
        count++;
    }
    stmt->close();
    con->commit();
    printf("%d Rows fetched\n",count);
    stmt->free();

    printf("SELECT * FROM T1 where F1='2009-11-10' and F2 >= ? and F3 <= ?;\n");
    strcpy(statement,"SELECT * FROM T1 where F1='2009-11-10' and  F2 >= ? and F3 <= ?;");
    stmt->prepare(statement);
    f2var=1;
    strcpy(f3var,"Nihar3");
    stmt->setIntParam(1,f2var);
    stmt->setStringParam(2,f3var);
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,f3var);
    count=0;
    con->beginTrans();
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
       printf("F1=%02d-%02d-%02d | F2=%d | F3=%s",f1var.year(), f1var.month(), f1var.dayOfMonth(), f2var,f3var);
        printf("\n");
        count++;
    }
    stmt->close();
    con->commit();
    printf("%d Rows fetched\n",count);
    stmt->free();

    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 5; }
    printf("Table dropped\n");
    stmt->free(); delete stmt; delete con; 
    return 0;
} 	 	      
