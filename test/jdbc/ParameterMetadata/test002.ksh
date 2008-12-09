#!/bin/sh
TESTFILE=${PWD}/jdbc/ParameterMetadata/ParaMetaTest2.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/ParameterMetadata
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ParaMetaTest2
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
