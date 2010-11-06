/*
 Char and varchar field length should not be more than 8000 bytes.
 CREATE TABLE t1(f1 INT,f2 CHAR(8002)); It should be failed because size should not greater than 8000
 CREATE TABLE t1(f1 INT,f2 VARCHAR(8002)); It should be failed because size should not greater than 8000
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
    strcpy(statement,"CREATE TABLE t1(f1 INT,f2 CHAR(8002));");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv==OK) { 
	strcpy(statement,"DROP TABLE t1;");
	rv = stmt->prepare(statement);
	if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
	rv = stmt->execute(rows);
	if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
	printf("Table dropped\n");
	stmt->free();
	delete stmt; 
	con->disconnect(); 
	delete con; 
	return 5;
    }
    printf("Table Creation Failed\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE t1(f1 INT,f2 VARCHAR(8002));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    rv = stmt->execute(rows);
    if(rv==OK) { 
	strcpy(statement,"DROP TABLE t1;");
	rv = stmt->prepare(statement);
	if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
	rv = stmt->execute(rows);
	if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
	printf("Table dropped\n");
	stmt->free();
	delete stmt; 
	con->disconnect(); 
	delete con; 
	return 9;
    }
    printf("Table Creation Failed\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
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

