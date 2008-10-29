#!/bin/sh
TESTFILE=${PWD}/jdbc/Statement/StmtTest6.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java StmtTest6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
