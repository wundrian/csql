/*
  Primary key(t1) and foreign key(t2) testing, for all datatypes.
  try to drop t1 . it should fail.
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
    strcpy(statement,"CREATE TABLE pkeyTINY(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f1));");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyTINY(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f1) references pkeyTINY(f1));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyTINY;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 6; }
    printf("Pkey table pkeyTINY can not be dropped withouting dropping Fkey Table fkeyTINY\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeySMALL(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f2));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeySMALL(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f2) references pkeySMALL(f2));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeySMALL;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 11; }
    printf("Pkey table pkeySMALL can not be dropped withouting dropping Fkey Table fkeySMALL\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyINT(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f3));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyINT(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f3) references pkeyINT(f3));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyINT;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 16; }
    printf("Pkey table pkeyINT can not be dropped withouting dropping Fkey Table fkeyINT\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyBIG(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f4));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 17; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 18; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyBIG(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f4) references pkeyBIG(f4));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 19; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 20; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyBIG;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 21; }
    printf("Pkey table pkeyBIG can not be dropped withouting dropping Fkey Table fkeyBIG\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyCHAR(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f5));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 22; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 23; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyCHAR(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f5) references pkeyCHAR(f5));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 24; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 25; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyCHAR;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 26; }
    printf("Pkey table pkeyCHAR can not be dropped withouting dropping Fkey Table fkeyCHAR\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyVARCHAR(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f6));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 27; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 28; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyVARCHAR(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f6) references pkeyVARCHAR(f6));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 29; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 30; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyVARCHAR;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 31; }
    printf("Pkey table pkeyVARCHAR can not be dropped withouting dropping Fkey Table fkeyVARCHAR\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyDATE(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f9));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 32; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 33; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyDATE(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f9) references pkeyDATE(f9));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 34; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 35; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyDATE;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 36; }
    printf("Pkey table pkeyDATE can not be dropped withouting dropping Fkey Table fkeyDATE\n");
    stmt->free();

    strcpy(statement,"CREATE TABLE pkeyTIME(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, primary key(f10));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 37; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 38; }
    stmt->free();
    
    strcpy(statement,"CREATE TABLE fkeyTIME(f1 TINYINT NOT NULL,f2 SMALLINT NOT NULL,f3 INT NOT NULL,f4 BIGINT NOT NULL,f5 CHAR(20) NOT NULL,f6 VARCHAR(30) NOT NULL,f7 FLOAT NOT NULL,f8 DOUBLE NOT NULL,f9 DATE NOT NULL,f10 TIME NOT NULL,f11 TIMESTAMP NOT NULL, foreign key(f10) references pkeyTIME(f10));");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 39; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 40; }
    stmt->free();
    
    rv = stmt->prepare("DROP TABLE pkeyTIME;");
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 41; }
    printf("Pkey table pkeyTIME can not be dropped withouting dropping Fkey Table fkeyTIME\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 42; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 43; }
    printf("\t TABLES\n");
    printf("\t--------\n");
    while(stmt->next() !=NULL) {
	printf("\t%s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Droping tables
    rv = stmt->prepare("DROP TABLE fkeyTINY;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 44; }
    printf("fkeyTINY Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyTINY;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 45; }
    printf("pkeyTINY Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeySMALL;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 46; }
    printf("fkeySMALL Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeySMALL;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 47; }
    printf("pkeySMALL Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyINT;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 48; }
    printf("fkeyINT Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyINT;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 49; }
    printf("pkeyINT Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyBIG;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 50; }
    printf("fkeyBIG Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyBIG;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 51; }
    printf("pkeyBIG Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 52; }
    printf("fkeyCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 53; }
    printf("pkeyCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyVARCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 54; }
    printf("fkeyVARCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyVARCHAR;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 55; }
    printf("pkeyVARCHAR Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyDATE;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 56; }
    printf("fkeyDATE Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyDATE;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 57; }
    printf("pkeyDATE Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE fkeyTIME;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 58; }
    printf("fkeyTIME Table Dropped\n");
    stmt->free();
    rv = stmt->prepare("DROP TABLE pkeyTIME;");
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 59; }
    printf("pkeyTIME Table Dropped\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 60; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 61; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }

    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

