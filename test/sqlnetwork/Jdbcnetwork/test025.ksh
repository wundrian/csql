#!/bin/sh
# CREATE TABLE T1 (f1 integer, f2 smallint, f3 tinyint,f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest5
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
