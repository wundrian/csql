#!/bin/sh
# Create a table and index for that table. Then do (INSERT/UPDATE/DELETE/SELECT) with no params statement.
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest2
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
