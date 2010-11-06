/*
  CopyStatement Testing.(field level and table level).
  CREATE TABLE MASTER(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);
  CREATE TABLE COPYMASTER AS SELECT * FROM MASTER;
  CREATE TABLE COPYMASTER_FIELDLEVEL AS SELECT f2,f5,f1,f9,f11,f10,f6,f4,f7,f3 FROM MASTER;
  CREATE TABLE COPYMASTER_DUPLICATEFIELD AS SELECT f2,f5,f2 FROM MASTER; This should be failed
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
    strcpy(statement,"CREATE TABLE MASTER(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    printf("Table MASTER Created\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE COPYMASTER AS SELECT * FROM MASTER;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    printf("Table COPYMASTER Created\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE COPYMASTER_FIELDLEVEL AS SELECT f2,f5,f1,f9,f11,f10,f6,f4,f7,f3 FROM MASTER;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    printf("Table COPYMASTER_FIELDLEVEL Created\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE COPYMASTER_DUPLICATEFIELD AS SELECT f2,f5,f2 FROM MASTER;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 8; }
    printf("Table COPYMASTER_DUPLICATEFIELD can not be Created because of duplicate fields\n");
    
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    printf("\t TABLES\n");
    printf("\t--------\n");
    while(stmt->next() !=NULL) {
	printf("\t%s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Droping tables
    rv = stmt->prepare("DROP TABLE MASTER;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("MASTER Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE COPYMASTER;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    printf("COPYMASTER Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE COPYMASTER_FIELDLEVEL;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("COPYMASTER_FIELDLEVEL Table Dropped\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }

    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

