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
    stmt2->setConnection(con);
    stmt3->setConnection(con);
    int rows=0;
    void *f1varT1 = NULL;
    void *f1varT2 = NULL;
    void *f1varT3 = NULL;
//  insert records into T1
    if(strcmp(getenv("DSN"),"oracle")==0) { 
        f1varT1 = malloc(sizeof(long long)); 
        f1varT2 = malloc(sizeof(long long));
        f1varT3 = malloc(sizeof(long long));
    } else {    
        f1varT1 = malloc(sizeof(int)); 
        f1varT2 = malloc(sizeof(int));
        f1varT3 = malloc(sizeof(int));
    }
    char f2varT1[36] = "lakshya";
    printf("Inserting records into table T1\n");
    strcpy(statement,"INSERT INTO T1 VALUES(?,?);");
    rv = stmt1->prepare(statement);
    if(rv!=OK) { delete stmt1; delete con; return 3; }
    int count=0;
    rv = con->beginTrans();
    for(int j=0;j<5;j++) {	
        if(strcmp(getenv("DSN"),"oracle")==0) {
            *(long long *) f1varT1 = j;
            stmt1->setLongLongParam(1,*(long long *)f1varT1);
        } else {
            *(int *) f1varT1 = j; 
            stmt1->setIntParam(1,*(int *) f1varT1);
        }
        stmt1->setStringParam(2,f2varT1);
        rv = stmt1->execute(rows);
        if(rv!=OK)break;
	    count++;
    }
    printf("%d rows inserted into table T1\n",count);

//  insert records into T2
    char f2varT2[36] = "lakshya";
    printf("Inserting records into table T2\n");
    strcpy(statement,"INSERT INTO T2 VALUES(?,?);");
    rv = stmt2->prepare(statement);
    if(rv!=OK) { delete stmt2; delete con; return 3; }
    count=0;
    for(int j=5;j<10;j++) {	
        if(strcmp(getenv("DSN"),"oracle")==0) {
            *(long long *) f1varT2 = j;
            stmt2->setLongLongParam(1,*(long long *)f1varT2);
        } else {
            *(int *) f1varT2 = j;      
            stmt2->setIntParam(1,*(int *) f1varT2);
        }
        stmt2->setStringParam(2,f2varT2);
        rv = stmt2->execute(rows);
        if(rv!=OK)break;
        count++;
    }
    printf("%d rows inserted into table T2\n",count);

//  insert records into T3
    char f2varT3[36] = "lakshya";
    printf("Inserting records into table T3\n");
    strcpy(statement,"INSERT INTO T3 VALUES(?,?);");
    rv = stmt3->prepare(statement);
    if(rv!=OK) { delete stmt3; delete con; return 3; }
    count=0;
    for(int j=10;j<15;j++) {	
        if(strcmp(getenv("DSN"),"oracle")==0) {
            *(long long *) f1varT3 = j;
            stmt3->setLongLongParam(1,*(long long *)f1varT3);
        } else {
            *(int *) f1varT3 = j;      
            stmt3->setIntParam(1,*(int *) f1varT3);
        }
        stmt3->setStringParam(2,f2varT3);
        rv = stmt3->execute(rows);
        if(rv!=OK)break;
        count++;
    }
    printf("%d rows inserted into table T3\n",count);
    rv = con->commit();
    
    free(f1varT1); free(f1varT2); free(f1varT3);
    stmt1->free(); delete stmt1; 
    stmt2->free(); delete stmt2; 
    stmt3->free(); delete stmt3; 
    delete con; 
    return 0;
}
