#!/bin/sh
#Open a connection and then close it. After that execute INSERT/QUERY/UPDATE statement. It should fail [StmtTest3.java]
TESTFILE=${PWD}/sqlnetwork/Jdbcnetwork/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/sqlnetwork/Jdbcnetwork
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest3
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
