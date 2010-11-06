#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest2
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
