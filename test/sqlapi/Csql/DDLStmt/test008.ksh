#!/bin/ksh
# Create Tree indexes on the fields which are (TINYINT,SMALLINT,INT,BIGINT,CHAR,VARCHAR,DATE,TIME).
# CREATE TABLE t1(f1 TINYINT ,f2 SMALLINT ,f3 INT ,f4 BIGINT ,f5 CHAR(20) ,f6 VARCHAR(30) ,f7 FLOAT ,f8 DOUBLE ,f9 DATE ,f10 TIME ,f11 TIMESTAMP); 
# CREATE INDEX idxtiny ON t1(f1) TREE;
# CREATE INDEX idxsmall ON t1(f2) TREE;
# CREATE INDEX idxint ON t1(f3) TREE;
# CREATE INDEX idxbig ON t1(f4) TREE;
# CREATE INDEX idxchar ON t1(f5) TREE;
# CREATE INDEX idxvarchar ON t(f6) TREE;
# CREATE INDEX idxfloat ON t1(f7) TREE;
# CREATE INDEX idxdouble ON t1(f8) TREE;
# CREATE INDEX idxdate ON t(f9) TREE;
# CREATE INDEX idxtime ON t1(f10) TREE;
# CREATE INDEX idxtimestamp ON t1(f11) TREE;
# All the indexes needs to be created

FILE=${PWD}/sqlapi/Csql/DDLStmt/treeindexonalldatatype
REL_PATH=.
if [ -s "$FILE" ]
then
    REL_PATH=`pwd`/sqlapi/Csql/DDLStmt
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/treeindexonalldatatype
else
    $REL_PATH/treeindexonalldatatype
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
