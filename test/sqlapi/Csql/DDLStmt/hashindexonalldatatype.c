/*
 Create Hash indexes on the fields which are (TINYINT,SMALLINT,INT,BIGINT,CHAR,VARCHAR,DATE,TIME).
 CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP); 
 CREATE INDEX idxtiny ON t1(f1) HASH;
 CREATE INDEX idxsmall ON t1(f2) HASH;
 CREATE INDEX idxint ON t1(f3) HASH;
 CREATE INDEX idxbig ON t1(f4) HASH;
 CREATE INDEX idxchar ON t1(f5) HASH;
 CREATE INDEX idxvarchar ON t(f6) HASH;
 CREATE INDEX idxdate ON t1(f7) HASH;
 CREATE INDEX idxtime ON t1(f8) HASH;
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
    
    strcpy(statement,"CREATE INDEX idxtiny ON t1(f1) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    printf("Hash Index Created on TINYINT field f1\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxsmall ON t1(f2) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    printf("Hash Index Created on SMALLINT field f2\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxint ON t1(f3) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    printf("Hash Index Created on INT field f3\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxbig ON t1(f4) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Hash Index Created on BIGINT field f4\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxchar ON t1(f5) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("Hash Index Created on CHAR field f5\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxvarchar ON t1(f6) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    printf("Hash Index Created on VARCHAR field f6\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxdate ON t1(f9) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 16; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 17; }
    printf("Hash Index Created on DATE field f9\n");
    stmt->free();
    
    strcpy(statement,"CREATE INDEX idxtime ON t1(f10) HASH;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 18; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 19; }
    printf("Hash Index Created on TIME field f10\n");
    stmt->free();
    
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 20; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 21; }
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

