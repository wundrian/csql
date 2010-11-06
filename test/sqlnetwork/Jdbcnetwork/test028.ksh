#!/bin/ksh
# NULL Tset INSERT null values to some fields with and without parameters
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest8.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest8
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
