#!/bin/ksh
# Create Hash indexes on the fields which are (TINYINT,SMALLINT,INT,BIGINT,CHAR,VARCHAR,DATE,TIME).
# CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP); 
# CREATE INDEX idxtiny ON t1(f1) HASH;
# CREATE INDEX idxsmall ON t1(f2) HASH;
# CREATE INDEX idxint ON t1(f3) HASH;
# CREATE INDEX idxbig ON t1(f4) HASH;
# CREATE INDEX idxchar ON t1(f5) HASH;
# CREATE INDEX idxvarchar ON t(f6) HASH;
# CREATE INDEX idxdate ON t1(f7) HASH;
# CREATE INDEX idxtime ON t1(f8) HASH;
# All the indexes needs to be created

FILE=${PWD}/sqlapi/Csql/DDLStmt/hashindexonalldatatype
REL_PATH=.
if [ -s "$FILE" ]
then
    REL_PATH=`pwd`/sqlapi/Csql/DDLStmt
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/hashindexonalldatatype
else
    $REL_PATH/hashindexonalldatatype
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
