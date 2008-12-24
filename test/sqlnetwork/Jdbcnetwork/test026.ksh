#!/bin/sh
# select tuple with WHERE clause having param for some fields(SELECT * FROM T1 WHERE f1=?AND f2=? AND f3=?)
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest6.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
echo "SELECT * FROM T1 WHERE f1=?AND f2=? AND f3=?"
java StmtTest6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
