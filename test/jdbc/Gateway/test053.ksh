#!/bin/sh
# Connect with connectstring "jdbc:gateway"
# CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint,f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);
# insert 9 tuples with params for all fields (INSERT INTO T1 values (?,?,?,?,?,?,?,?,?))
# select tuple with WHERE clause having param for each fields(SELECT * FROM T1 WHERE f1=?, SELECT * from T1 where f2=?)
# GwTest13.java

TESTFILE=${PWD}/jdbc/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo "CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);" >${REL_PATH}/t1create.sql
isql $DSN < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
java GwTest13
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "drop table T1;">${REL_PATH}/dp.sql
isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

exit 0;
