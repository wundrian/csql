/*
  Autoincrement key should not be allowed for the datatypes other than all int types.
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
    strcpy(statement,"CREATE TABLE AUTOINCTINY(f1 TINYINT AUTO_INCREMENT,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCSMALL(f1 TINYINT ,f2 SMALLINT AUTO_INCREMENT,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCINT(f1 TINYINT ,f2 SMALLINT ,f3 INT AUTO_INCREMENT,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCBIG(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT AUTO_INCREMENT,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCCHAR(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) AUTO_INCREMENT,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 9; }
    printf("Auto_increment can not be applied on char datatype\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCVARCHAR(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) AUTO_INCREMENT,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Auto_increment can not be applied on varchar datatype\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE AUTOINCFLOAT(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT AUTO_INCREMENT,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 13; }
    printf("Auto_increment can not be applied on float datatype\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCDOUBLE(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE AUTO_INCREMENT,f9 DATE ,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 15; }
    printf("Auto_increment can not be applied on double datatype\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE AUTOINCDATE(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE AUTO_INCREMENT,f10 TIME ,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 17; }
    printf("Auto_increment can not be applied on date datatype\n");
    stmt->free();
    
    strcpy(statement,"CREATE TABLE AUTOINCTIME(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME AUTO_INCREMENT,f11 TIMESTAMP);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 19; }
    printf("Auto_increment can not be applied on time datatype\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE AUTOINCTIMESTAMP(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP AUTO_INCREMENT);");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 21; }
    printf("Auto_increment can not be applied on timestamp datatype\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 23; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 24; }
    printf("\t TABLES\n");
    printf("\t--------\n");
    while(stmt->next() !=NULL) {
	printf("\t%s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Droping tables
    rv = stmt->prepare("DROP TABLE AUTOINCTINY;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 25; }
    printf("AUTOINCTINY Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCSMALL;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 26; }
    printf("AUTOINCSMALL Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCINT;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 27; }
    printf("AUTOINCINT Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCBIG;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 28; }
    printf("AUTOINCBIG Table Dropped\n");
    stmt->free();
/*    rv = stmt->prepare("DROP TABLE AUTOINCCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 53; }
    printf("AUTOINCCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCVARCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 55; }
    printf("AUTOINCVARCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCDATE;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 57; }
    printf("AUTOINCDATE Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE AUTOINCTIME;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 59; }
    printf("AUTOINCTIME Table Dropped\n");
    stmt->free();*/

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 29; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 30; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }

    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

