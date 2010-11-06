#!/bin/ksh
# Testing LIKE, IN Operators with varchar
# CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
# INSERT INTO t1 VALUES(1, 'ABCD');
# INSERT INTO t1 VALUES(2, 'ABCDE');
# INSERT INTO t1 VALUES(3, 'ABCEF');
# INSERT INTO t1 VALUES(4, 'ABCCF');
# INSERT INTO t1 VALUES(5, 'ABCFF');
# INSERT INTO t1 VALUES(6, 'ABCDG');
# INSERT INTO t1 VALUES(7, 'ABDCG');
# Test the below queries return proper result set or not.
# select * from t1;
# select * from t1 where f2 like 'ABC%';
# select * from t1 where f2 like 'ABCD%';
# select * from t1 where f2 like 'ABC%F';
# select * from t1 where f2 in ('ABCDE','ABCCF','ABCDG');
# select * from t1 where f2 in ('ABCDE','ADCBF','ABCDG');
# The below statement should be fail, saying "Condition value should not be NULL"
# select * from t1 where f2 in ('ABCDE','ADCBF',NULL);
#
CREATEFILE=${PWD}/sql/Predicate/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Predicate
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_like_in.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_like_in.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/dropt1.sql
exit 0;
