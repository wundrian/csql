#!/bin/ksh
# Select Data with Field name instead of position  
# TestScript6.java

TESTFILE=${PWD}/jdbc/network/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
