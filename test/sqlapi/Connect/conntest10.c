/*  create table T1 ,ISERT ,UPDATE AND COMMIT.
 *  FETCH UPDATED RECORDS.

 *  Author : Jitendra Lenka
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK)return 1;
    printf("Connection opened\n");
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 INT);");
    int rows = 0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 3; }
    stmt->free();
    printf("Table T1 CREATED\n");
    // insert into statement  
    strcpy(statement,"INSERT INTO T1 VALUES(1,1);");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = con->beginTrans();
    if(rv!=OK) { delete stmt; delete con; return 5; }
    rv = stmt->execute(rows); if(rv!=OK) return 6;
    stmt->free();
    printf("One record inserted\n");
    // update statement 
    printf("update T1 set F2=100\n");
    strcpy(statement,"UPDATE T1 SET F2=100;");
    rv = stmt->prepare(statement);
    if(rv !=OK) { delete stmt; delete con; return 7; }
    rv = stmt->execute(rows);
    if(rv!=OK){ printf ("Hello\n"); return 8; }
    rv  = con->commit(); if(rv!=OK)return 9;
    printf("One row updated\n");
    strcpy(statement,"SELECT F2 FROM T1 ;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 10; }
    int id=10;
    stmt->bindField(1,&id);
    rv = con->beginTrans();
    if(rv!=OK)return 11;
    stmt->execute(rows);
    int count=0;
    while(stmt->fetch()!=NULL) {
        printf("F2= %d\n",id);
        count++;
    }
    stmt->close();
    rv = con->commit();
    if(rv!=OK)return 12;
    printf("Total record fetched=%d\n",count);
    stmt->free();
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 13; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 14; }
    printf("TABLE T1 DROPPED SUCCESSFULLY\n");
    stmt->free(); delete stmt; delete con; 
    printf("Connection closed successfully\n");
    return 0;
}    
