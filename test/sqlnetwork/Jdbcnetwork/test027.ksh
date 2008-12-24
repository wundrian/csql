#!/bin/sh
# update tuple with SET and WHERE clause having params (UPDATE T1 SET f2=?, f8=? WHERE f1=?AND f9=?)
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest7.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest7
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
