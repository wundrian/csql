#!/bin/sh
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
