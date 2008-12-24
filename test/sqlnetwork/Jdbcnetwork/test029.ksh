#!/bin/sh
# update tuple with SET and WHERE clause having params (UPDATE T1 SET f2=NULL, f6=NULL WHERE f1=?AND f9=?)

TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest9.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest9
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
