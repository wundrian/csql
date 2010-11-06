#!/bin/ksh
TESTFILE=${PWD}/jdbc/ParameterMetadata/ParaMetaTest3.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/ParameterMetadata
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ParaMetaTest3
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
