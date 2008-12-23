#!/bin/sh
# Connect with connectstring "jdbc:gateway" 
# Then do (INSERT/UPDATE/DELETE/SELECT) with params statement using gateway statement
# It should pass.when csqlserver is not runnig
# GwTest10.java

TESTFILE=${PWD}/jdbc/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo "create table T1 (f1 int,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql
isql $DSN < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
java GwTest10 
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "drop table T1;">${REL_PATH}/dp.sql
isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

exit 0;
