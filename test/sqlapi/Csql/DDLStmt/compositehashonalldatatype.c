/*
 CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);

 CREATE INDEX idxtinyint_smallint ON t1(f1,f2) HASH;
 CREATE INDEX idxtinyint_int ON t1(f1,f3) HASH;
 CREATE INDEX idxtinyint_bigint ON t1(f1,f4) HASH;
 CREATE INDEX idxtinyint_char ON t1(f1,f5) HASH;
 CREATE INDEX idxtinyint_varchar ON t1(f1,f6) HASH;
 CREATE INDEX idxtinyint_date ON t1(f1,f9) HASH;
 CREATE INDEX idxtinyint_time ON t1(f1,f10) HASH;

 CREATE INDEX idxsmallint_tinyint ON t1(f2,f1) HASH; should fail
 CREATE INDEX idxsmallint_int ON t1(f2,f3) HASH;
 CREATE INDEX idxsmallint_bigint ON t1(f2,f4) HASH;
 CREATE INDEX idxsmallint_char ON t1(f2,f5) HASH;
 CREATE INDEX idxsmallint_varchar ON t1(f2,f6) HASH;
 CREATE INDEX idxsmallint_date ON t1(f2,f9) HASH;
 CREATE INDEX idxsmallint_time ON t1(f2,f10) HASH;

 CREATE INDEX idxint_tinyint ON t1(f3,f1) HASH; should fail
 CREATE INDEX idxint_smallint ON t1(f3,f2) HASH; should fail
 CREATE INDEX idxint_bigint ON t1(f3,f4) HASH;
 CREATE INDEX idxint_char ON t1(f3,f5) HASH;
 CREATE INDEX idxint_varchar ON t1(f3,f6) HASH;
 CREATE INDEX idxint_date ON t1(f3,f9) HASH;
 CREATE INDEX idxint_time ON t1(f3,f10) HASH;

 CREATE INDEX idxbigint_tinyint ON t1(f4,f1) HASH; should fail
 CREATE INDEX idxbigint_smallint ON t1(f4,f2) HASH; should fail
 CREATE INDEX idxbigint_int ON t1(f4,f3) HASH; should fail
 CREATE INDEX idxbigint_char ON t1(f4,f5) HASH;
 CREATE INDEX idxbigint_varchar ON t1(f4,f6) HASH;
 CREATE INDEX idxbigint_date ON t1(f4,f9) HASH;
 CREATE INDEX idxbigint_time ON t1(f4,f10) HASH;

 CREATE INDEX idxchar_tinyint ON t1(f5,f1) HASH; should fail 
 CREATE INDEX idxchar_smallint ON t1(f5,f2) HASH; should fail
 CREATE INDEX idxchar_int ON t1(f5,f3) HASH; should fail
 CREATE INDEX idxchar_bigint ON t1(f5,f4) HASH; should fail
 CREATE INDEX idxchar_varchar ON t1(f5,f6) HASH;
 CREATE INDEX idxchar_date ON t1(f5,f9) HASH;
 CREATE INDEX idxchar_time ON t1(f5,f10) HASH;

 CREATE INDEX idxvarchar_tinyint ON t1(f6,f1) HASH; should fail
 CREATE INDEX idxvarchar_smallint ON t1(f6,f2) HASH; should fail
 CREATE INDEX idxvarchar_int ON t1(f6,f3) HASH; should fail 
 CREATE INDEX idxvarchar_bigint ON t1(f6,f4) HASH; should fail 
 CREATE INDEX idxvarchar_char ON t1(f6,f5) HASH; should fail 
 CREATE INDEX idxvarchar_date ON t1(f6,f9) HASH; 
 CREATE INDEX idxvarchar_time ON t1(f6,f10) HASH;

 CREATE INDEX idxdate_tinyint ON t1(f9,f1) HASH; should fail 
 CREATE INDEX idxdate_smallint ON t1(f9,f2) HASH; should fail 
 CREATE INDEX idxdate_int ON t1(f9,f3) HASH; should fail 
 CREATE INDEX idxdate_bigint ON t1(f9,f4) HASH; should fail 
 CREATE INDEX idxdate_char ON t1(f9,f5) HASH; should fail 
 CREATE INDEX idxdate_date ON t1(f9,f6) HASH; should fail
 CREATE INDEX idxdate_time ON t1(f9,f10) HASH;

 CREATE INDEX idxtime_tinyint ON t1(f10,f1) HASH; should fail 
 CREATE INDEX idxtime_smallint ON t1(f10,f2) HASH; should fail 
 CREATE INDEX idxtime_int ON t1(f10,f3) HASH; should fail 
 CREATE INDEX idxtime_bigint ON t1(f10,f4) HASH; should fail 
 CREATE INDEX idxtime_char ON t1(f10,f5) HASH; should fail 
 CREATE INDEX idxtime_date ON t1(f10,f6) HASH; should fail 
 CREATE INDEX idxtime_time ON t1(f10,f9) HASH; should fail 

 CREATE INDEX idxtinyint_smallint_int ON t1(f1,f2,f3) HASH;
 CREATE INDEX idxtinyint_smallint_int_bigint ON t1(f1,f2,f3,f4) HASH;
 CREATE INDEX idxtinyint_smallint_int_bigint_char ON t1(f1,f2,f3,f4,f5) HASH;
 CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar ON t1(f1,f2,f3,f4,f5,f6) HASH;
 CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date ON t1(f1,f2,f3,f4,f5,f6,f9) HASH;
 CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date_time ON t1(f1,f2,f3,f4,f5,f6,f9,f10) HASH;

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
    
    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint ON t1(f1,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_int ON t1(f1,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 6; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_bigint ON t1(f1,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 7; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_char ON t1(f1,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_varchar ON t1(f1,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_date ON t1(f1,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 14; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 15; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_time ON t1(f1,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 16; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 17; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_tinyint ON t1(f2,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 18; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 19; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_int ON t1(f2,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 20; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 21; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_bigint ON t1(f2,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 22; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 23; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_char ON t1(f2,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 24; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 25; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_varchar ON t1(f2,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 26; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 27; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_date ON t1(f2,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 28; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 29; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxsmallint_time ON t1(f2,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 30; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 31; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_tinyint ON t1(f3,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 32; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 33; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_smallint ON t1(f3,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 34; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 35; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_bigint ON t1(f3,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 36; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 37; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_char ON t1(f3,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 38; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 39; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_varchar ON t1(f3,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 40; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 41; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_date ON t1(f3,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 42; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 43; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxint_time ON t1(f3,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 44; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 45; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_tinyint ON t1(f4,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 46; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 47; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_smallint ON t1(f4,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 48; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 49; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_int ON t1(f4,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 50; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 51; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_char ON t1(f4,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 52; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 53; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_varchar ON t1(f4,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 54; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 55; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_date ON t1(f4,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 55; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 56; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxbigint_time ON t1(f4,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 57; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 58; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_tinyint ON t1(f5,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 59; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 60; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_smallint ON t1(f5,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 61; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 62; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_int ON t1(f5,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 63; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 64; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_bigint ON t1(f5,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 65; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 66; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_varchar ON t1(f5,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 67; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 68; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_date ON t1(f5,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 69; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 70; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxchar_time ON t1(f5,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 71; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 72; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_tinyint ON t1(f6,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 73; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 74; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_smallint ON t1(f6,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 75; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 76; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_int ON t1(f6,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 77; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 78; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_bigint ON t1(f6,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 79; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 80; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_char ON t1(f6,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 81; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 82; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_date ON t1(f6,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 83; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 84; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxvarchar_time ON t1(f6,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 85; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 86; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_tinyint ON t1(f9,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 87; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 88; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_smallint ON t1(f9,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 89; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 90; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_int ON t1(f9,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 91; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 92; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_bigint ON t1(f9,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 93; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 94; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_char ON t1(f9,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 95; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 96; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_date ON t1(f9,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 97; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 98; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxdate_time ON t1(f9,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 99; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 100; }
    printf("Index Created\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_tinyint ON t1(f10,f1) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 101; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 102; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_smallint ON t1(f10,f2) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 103; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 104; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_int ON t1(f10,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 105; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 106; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_bigint ON t1(f10,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 107; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 108; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_char ON t1(f10,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 109; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 110; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_date ON t1(f10,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 111; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 112; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtime_time ON t1(f10,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 113; }
    rv = stmt->execute(rows);
    if(rv==OK) { delete stmt; con->disconnect(); delete con; return 114; }
    printf("Index Already Exist\n");
    stmt->free();
   
    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int ON t1(f1,f2,f3) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 115; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 116; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int_bigint ON t1(f1,f2,f3,f4) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 117; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 118; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int_bigint_char ON t1(f1,f2,f3,f4,f5) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 119; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 120; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar ON t1(f1,f2,f3,f4,f5,f6) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 121; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 122; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date ON t1(f1,f2,f3,f4,f5,f6,f9) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 123; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 124; }
    printf("Index Created\n");
    stmt->free();

    rv = stmt->prepare("CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date_time ON t1(f1,f2,f3,f4,f5,f6,f9,f10) HASH;");
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 125; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 126; }
    printf("Index Created\n");
    stmt->free();

// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 127; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 128; }
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

