#!/bin/ksh
TESTFILE=${PWD}/jdbc/ResultSetMetaData/RSMetadata1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/ResultSetMetaData
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java RSMetadata2 
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
