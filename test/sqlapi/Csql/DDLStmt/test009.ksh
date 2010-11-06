#!/bin/ksh
# Composite tree index testing
# CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP);

# CREATE INDEX idxtinyint_smallint ON t1(f1,f2) HASH;
# CREATE INDEX idxtinyint_int ON t1(f1,f3) HASH;
# CREATE INDEX idxtinyint_bigint ON t1(f1,f4) HASH;
# CREATE INDEX idxtinyint_char ON t1(f1,f5) HASH;
# CREATE INDEX idxtinyint_varchar ON t1(f1,f6) HASH;
# CREATE INDEX idxtinyint_date ON t1(f1,f9) HASH;
# CREATE INDEX idxtinyint_time ON t1(f1,f10) HASH;

# CREATE INDEX idxsmallint_tinyint ON t1(f2,f1) HASH; should fail
# CREATE INDEX idxsmallint_int ON t1(f2,f3) HASH;
# CREATE INDEX idxsmallint_bigint ON t1(f2,f4) HASH;
# CREATE INDEX idxsmallint_char ON t1(f2,f5) HASH;
# CREATE INDEX idxsmallint_varchar ON t1(f2,f6) HASH;
# CREATE INDEX idxsmallint_date ON t1(f2,f9) HASH;
# CREATE INDEX idxsmallint_time ON t1(f2,f10) HASH;

# CREATE INDEX idxint_tinyint ON t1(f3,f1) HASH; should fail
# CREATE INDEX idxint_smallint ON t1(f3,f2) HASH; should fail
# CREATE INDEX idxint_bigint ON t1(f3,f4) HASH;
# CREATE INDEX idxint_char ON t1(f3,f5) HASH;
# CREATE INDEX idxint_varchar ON t1(f3,f6) HASH;
# CREATE INDEX idxint_date ON t1(f3,f9) HASH;
# CREATE INDEX idxint_time ON t1(f3,f10) HASH;

# CREATE INDEX idxbigint_tinyint ON t1(f4,f1) HASH; should fail
# CREATE INDEX idxbigint_smallint ON t1(f4,f2) HASH; should fail
# CREATE INDEX idxbigint_int ON t1(f4,f3) HASH; should fail
# CREATE INDEX idxbigint_char ON t1(f4,f5) HASH;
# CREATE INDEX idxbigint_varchar ON t1(f4,f6) HASH;
# CREATE INDEX idxbigint_date ON t1(f4,f9) HASH;
# CREATE INDEX idxbigint_time ON t1(f4,f10) HASH;

# CREATE INDEX idxchar_tinyint ON t1(f5,f1) HASH; should fail 
# CREATE INDEX idxchar_smallint ON t1(f5,f2) HASH; should fail
# CREATE INDEX idxchar_int ON t1(f5,f3) HASH; should fail
# CREATE INDEX idxchar_bigint ON t1(f5,f4) HASH; should fail
# CREATE INDEX idxchar_varchar ON t1(f5,f6) HASH;
# CREATE INDEX idxchar_date ON t1(f5,f9) HASH;
# CREATE INDEX idxchar_time ON t1(f5,f10) HASH;

# CREATE INDEX idxvarchar_tinyint ON t1(f6,f1) HASH; should fail
# CREATE INDEX idxvarchar_smallint ON t1(f6,f2) HASH; should fail
# CREATE INDEX idxvarchar_int ON t1(f6,f3) HASH; should fail 
# CREATE INDEX idxvarchar_bigint ON t1(f6,f4) HASH; should fail 
# CREATE INDEX idxvarchar_char ON t1(f6,f5) HASH; should fail 
# CREATE INDEX idxvarchar_date ON t1(f6,f9) HASH; 
# CREATE INDEX idxvarchar_time ON t1(f6,f10) HASH;

# CREATE INDEX idxdate_tinyint ON t1(f9,f1) HASH; should fail 
# CREATE INDEX idxdate_smallint ON t1(f9,f2) HASH; should fail 
# CREATE INDEX idxdate_int ON t1(f9,f3) HASH; should fail 
# CREATE INDEX idxdate_bigint ON t1(f9,f4) HASH; should fail 
# CREATE INDEX idxdate_char ON t1(f9,f5) HASH; should fail 
# CREATE INDEX idxdate_date ON t1(f9,f6) HASH; should fail
# CREATE INDEX idxdate_time ON t1(f9,f10) HASH;

# CREATE INDEX idxtime_tinyint ON t1(f10,f1) HASH; should fail 
# CREATE INDEX idxtime_smallint ON t1(f10,f2) HASH; should fail 
# CREATE INDEX idxtime_int ON t1(f10,f3) HASH; should fail 
# CREATE INDEX idxtime_bigint ON t1(f10,f4) HASH; should fail 
# CREATE INDEX idxtime_char ON t1(f10,f5) HASH; should fail 
# CREATE INDEX idxtime_date ON t1(f10,f6) HASH; should fail 
# CREATE INDEX idxtime_time ON t1(f10,f9) HASH; should fail 

# CREATE INDEX idxtinyint_smallint_int ON t1(f1,f2,f3) HASH;
# CREATE INDEX idxtinyint_smallint_int_bigint ON t1(f1,f2,f3,f4) HASH;
# CREATE INDEX idxtinyint_smallint_int_bigint_char ON t1(f1,f2,f3,f4,f5) HASH;
# CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar ON t1(f1,f2,f3,f4,f5,f6) HASH;
# CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date ON t1(f1,f2,f3,f4,f5,f6,f9) HASH;
# CREATE INDEX idxtinyint_smallint_int_bigint_char_varchar_date_time ON t1(f1,f2,f3,f4,f5,f6,f9,f10) HASH;

FILE=${PWD}/sqlapi/Csql/DDLStmt/compositehashonalldatatype
REL_PATH=.
if [ -s "$FILE" ]
then
    REL_PATH=`pwd`/sqlapi/Csql/DDLStmt
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/compositehashonalldatatype
else
    $REL_PATH/compositehashonalldatatype
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
   $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

echo "echo drop table t1;" >${REL_PATH}/drop_t1.sql
echo "drop table t1;" >>${REL_PATH}/drop_t1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t1.sql
rm -f ${REL_PATH}/drop_t1.sql 
exit 0
