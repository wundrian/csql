#!/bin/ksh
# ExecuteUpdate Should return no of records updated


TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest12 
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
