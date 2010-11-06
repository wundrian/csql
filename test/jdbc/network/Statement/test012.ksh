#!/bin/ksh
# ExecuteUpdate Should return no of records updated
# TestScript3.java

TESTFILE=${PWD}/jdbc/network/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript3
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
