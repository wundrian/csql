#!/bin/sh
# execute with select and getResultSet(). getUpdateCount() should return -1. 
# TestScript9.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript9
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
