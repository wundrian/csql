#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/DatabaseMetadata/DataMeta1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/DatabaseMetadata
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java DataMeta1 
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
