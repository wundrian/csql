/*One connection working with multiple statements
 *create table T1 with two fields,
 *One connection working with multiple statements simultaneously for csql,
 *Create conn
 *create 3 stmts for inserting into 5 tables and set the same connection
 *insert into all 3 tables and commit the transaction
 *free all stmts
 *select the records from 3 tables in same connection
 *free all stmt;
 *Author : Nihar Paital
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt1 = createStatement();
    AbsSqlStatement *stmt2 = createStatement();
    AbsSqlStatement *stmt3 = createStatement();
    char statement[200];

    stmt1->setConnection(con);
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20));");
    int rows=0;
    rv = stmt1->prepare(statement);
    if(rv!=OK) { delete stmt1; delete con; return 1; }
    rv = stmt1->execute(rows);
    if(rv!=OK) { delete stmt1; delete con; return 2; }
    printf("Table created\n");

    stmt2->setConnection(con);
    strcpy(statement,"CREATE TABLE T2(F1 INT,F2 CHAR(20));");
    rows=0;
    rv = stmt2->prepare(statement);
    if(rv!=OK) { delete stmt2; delete con; return 3; }
    rv = stmt2->execute(rows);
    if(rv!=OK) { delete stmt2; delete con; return 4; }
    printf("Table created\n");

    stmt3->setConnection(con);
    strcpy(statement,"CREATE TABLE T3(F1 INT,F2 CHAR(20));");
    rows=0;
    rv = stmt3->prepare(statement);
    if(rv!=OK) { delete stmt3; delete con; return 5; }
    rv = stmt3->execute(rows);
    if(rv!=OK) { delete stmt3; delete con; return 6; }
    printf("Table created\n");
    stmt1->free();
    stmt2->free();
    stmt3->free();

//  insert records into T1
    int f1varT1 = 1;
    char f2varT1[24] = "lakshya";
    printf("Inserting records into table T1\n");
    strcpy(statement,"INSERT INTO T1 VALUES(?,?);");
    rv = stmt1->prepare(statement);
    if(rv!=OK) { delete stmt1; delete con; return 3; }
    int count=0;
    rv = con->beginTrans();
    for(int j=0;j<5;j++) {	
            f1varT1 = j;
            if(rv!=OK)break;
            stmt1->setIntParam(1,f1varT1);
            stmt1->setStringParam(2,f2varT1);
            rv = stmt1->execute(rows);
            if(rv!=OK)break;
	    count++;
    }
    printf("%d rows inserted into table T1\n",count);

//  insert records into T2
    int f1varT2 = 1;
    char f2varT2[24] = "lakshya";
    printf("Inserting records into table T2\n");
    strcpy(statement,"INSERT INTO T2 VALUES(?,?);");
    rv = stmt2->prepare(statement);
    if(rv!=OK) { delete stmt2; delete con; return 3; }
    count=0;
    for(int j=5;j<10;j++) {	
            f1varT2 = j;
            if(rv!=OK)break;
            stmt2->setIntParam(1,f1varT2);
            stmt2->setStringParam(2,f2varT2);
            rv = stmt2->execute(rows);
            if(rv!=OK)break;
	    count++;
    }
    printf("%d rows inserted into table T2\n",count);

//  insert records into T3
    int f1varT3 = 1;
    char f2varT3[24] = "lakshya";
    printf("Inserting records into table T3\n");
    strcpy(statement,"INSERT INTO T3 VALUES(?,?);");
    rv = stmt3->prepare(statement);
    if(rv!=OK) { delete stmt3; delete con; return 3; }
    count=0;
    for(int j=10;j<15;j++) {	
            f1varT3 = j;
            if(rv!=OK)break;
            stmt3->setIntParam(1,f1varT3);
            stmt3->setStringParam(2,f2varT3);
            rv = stmt3->execute(rows);
            if(rv!=OK)break;
	    count++;
    }
    printf("%d rows inserted into table T3\n",count);
    rv = con->commit();

    stmt1->free();
    stmt2->free();
    stmt3->free();
//*******************************************
    printf("SELECT * FROM T1;\n");
    strcpy(statement,"SELECT * FROM T1;");
    rv = stmt1->prepare(statement);
    if(rv !=OK) { delete stmt1; delete con; return 4; }
    stmt1->bindField(1,&f1varT1);
    stmt1->bindField(2,f2varT1);
    void *ret;
    count = 0;
    rv = con->beginTrans();
    if(rv!=OK)return 5;
    printf("T1.f1\tT1.f2\n");
    stmt1->execute(rows);
    while((char*)stmt1->fetch()) {
        printf("%d\t%s\n",f1varT1,f2varT1);
        if(ret==NULL) {
		break;
	}
    }

    printf("SELECT * FROM T2;\n");
    strcpy(statement,"SELECT * FROM T2;");
    rv = stmt2->prepare(statement);
    if(rv !=OK) { delete stmt2; delete con; return 4; }
    stmt2->bindField(1,&f1varT2);
    stmt2->bindField(2,f2varT2);
    count = 0;
    stmt2->execute(rows);
    printf("T2.f1\tT2.f2\n");
    while((char*)stmt2->fetch()) {
        printf("%d\t%s\n",f1varT2,f2varT2);
        if(ret==NULL) {
               break;
        }     
    }

    printf("SELECT * FROM T3;\n");
    strcpy(statement,"SELECT * FROM T3;");
    rv = stmt3->prepare(statement);
    if(rv !=OK) { delete stmt3; delete con; return 4; }
    stmt3->bindField(1,&f1varT3);
    stmt3->bindField(2,f2varT3);
    count = 0;
    stmt3->execute(rows);
    printf("T3.f1\tT3.f2\n");
    while((char*)stmt3->fetch()) {
        printf("%d\t%s\n",f1varT3,f2varT3);
        if(ret==NULL) {
               break;
        }     
    }
    con->commit();

    strcpy(statement,"DROP TABLE T1;");
    rv = stmt1->prepare(statement);
    rv = stmt1->execute(rows);
    if(rv==OK){printf("Table T1 dropped successfully\n");}

    strcpy(statement,"DROP TABLE T2;");
    rv = stmt2->prepare(statement);
    rv = stmt2->execute(rows);
    if(rv==OK){printf("Table T2 dropped successfully\n");}

    strcpy(statement,"DROP TABLE T3;");
    rv = stmt3->prepare(statement);
    rv = stmt3->execute(rows);
    if(rv==OK){printf("Table T3 dropped successfully\n");}

    stmt1->free(); delete stmt1; 
    stmt2->free(); delete stmt2; 
    stmt3->free(); delete stmt3; 
    delete con; 
    return 0;
}
