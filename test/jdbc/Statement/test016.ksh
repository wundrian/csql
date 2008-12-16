#!/bin/sh
# executequery with ins, upd, del statements which will throw exception
# TestScript7.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript7
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
