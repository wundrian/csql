#!/bin/sh
#JDBC GATEWAY CACHE 
TESTFILE=${PWD}/jdbc/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}

echo "CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);" >${REL_PATH}/t1create.sql
isql $DSN < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -t T1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 2;
fi
java GwStmt10
if [ $? -ne 0 ]
then
   exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t T1 -u >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 4;
fi
echo "drop table T1;">${REL_PATH}/dp.sql
isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

exit 0;
