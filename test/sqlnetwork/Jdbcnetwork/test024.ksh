#!/bin/sh
# Open a connection and close it twice. It should give no error
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest4
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
