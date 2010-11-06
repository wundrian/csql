#!/bin/ksh
# Testing 'is null'/'is not null' Operators with varchar using Delete statement. ( )
# CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
# INSERT INTO t1 VALUES(1, 'ABCD');
# INSERT INTO t1 VALUES(2, 'NULL');
# INSERT INTO t1 VALUES(3, NULL);
# INSERT INTO t1 VALUES(4, 'ABCEF');
# INSERT INTO t1 (f1) VALUES (5);
# INSERT INTO t1 VALUES(6, 'ABCFF');
# Test the below queries return proper result set or not.
# select * from t1;
# DELETE FROM t1 where f2 IS NOT NULL;
# DELETE FROM t1 where f2 IS NULL;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_NULL_del.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_NULL_del.sql 
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
