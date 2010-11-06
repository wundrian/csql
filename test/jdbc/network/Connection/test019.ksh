#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest19
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
