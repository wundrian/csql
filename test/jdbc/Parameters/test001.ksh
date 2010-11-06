#!/bin/ksh
# select tuple with WHERE clause having param for some fields(SELECT * FROM T1 WHERE f1='Date value' AND f2=? AND f3=?)
# Create a table having f1 date, f2 tnt and f3 string
# Execute SELECT * FROM T1 WHERE f1='Date Value' AND f2=? AND f3=?;

TESTFILE=${PWD}/jdbc/Parameters/ParaTest1Date.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Parameters
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ParaTest1Date
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
