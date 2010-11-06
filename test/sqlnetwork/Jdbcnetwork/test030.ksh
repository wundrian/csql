#!/bin/ksh
# Create table. At the time of insertion , Insert some record with Null Value
# Check null inserted or not
# Test For setNull()
 

TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest10
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
