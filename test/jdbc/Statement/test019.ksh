#!/bin/sh
# Irrespective of number set in setFetchSize(), getFetchSize() should return 1 
# TestScript10.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript10
if [ $? -ne 0 ]
then
   echo "Drop table T1;"| $CSQL_INSTALL_ROOT/bin/csql 
   exit 1;
fi
exit 0;
