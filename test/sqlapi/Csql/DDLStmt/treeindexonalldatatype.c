/*
 Create Tree indexes on the fields which are (TINYINT,SMALLINT,INT,BIGINT,CHAR,VARCHAR,DATE,TIME).
 CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP); 
 CREATE INDEX idxtiny ON t1(f1) TREE;
 CREATE INDEX idxsmall ON t1(f2) TREE;
 CREATE INDEX idxint ON t1(f3) TREE;
 CREATE INDEX idxbig ON t1(f4) TREE;
 CREATE INDEX idxchar ON t1(f5) TREE;
 CREATE INDEX idxvarchar ON t(f6) TREE;
 CREATE INDEX idxfloat ON t1(f7) TREE;
 CREATE INDEX idxdouble ON t1(f8) TREE;
 CREATE INDEX idxdate ON t(f9) TREE;
 CREATE INDEX idxtime ON t1(f10) TREE;
 CREATE INDEX idxtimestamp ON t1(f11) TREE;
 All the indexes needs to be created
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
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    printf("Table t1 Created\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxtiny ON t1(f1) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    printf("Tree Index Created on TINYINT field f1\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxsmall ON t1(f2) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    printf("Tree Index Created on SMALLINT field f2\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxint ON t1(f3) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    printf("Tree Index Created on INT field f3\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxbig ON t1(f4) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Tree Index Created on BIGINT field f4\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxchar ON t1(f5) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("Tree Index Created on CHAR field f5\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxvarchar ON t1(f6) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    printf("Tree Index Created on VARCHAR field f6\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxfloat ON t1(f7) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 16; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 17; }
    printf("Tree Index Created on FLOAT field f7\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxdouble ON t1(f8) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 18; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 19; }
    printf("Tree Index Created on DOUBLE field f8\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxdate ON t1(f9) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 20; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 21; }
    printf("Tree Index Created on DATE field f9\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxtime ON t1(f10) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 22; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 23; }
    printf("Tree Index Created on TIME field f10\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxtimestamp ON t1(f11) TREE;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 24; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 25; }
    printf("Tree Index Created on TIMESTAMP field f11\n");
    stmt->free();
    
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 26; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 27; }
    printf("\t TABLES\n");
    printf("\t--------\n");
    while(stmt->next() !=NULL) {
	printf("\t%s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

