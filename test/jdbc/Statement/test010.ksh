#!/bin/sh
# Run csqlserver ,Create table. At the time of insertion , Insert some record with Null Value
# Check null inserted or not
# Test For setNull()
# TestScript1.java

TESTFILE=${PWD}/jdbc/Statement/StmtTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java TestScript1
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
