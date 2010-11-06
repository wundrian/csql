#!/bin/ksh
TESTFILE=${PWD}/jdbc/DatabaseMetadata/DataMeta1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/DatabaseMetadata
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java DataMeta4 
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
