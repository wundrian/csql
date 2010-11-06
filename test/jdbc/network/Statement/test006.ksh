#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/Statement/StmtTest6.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
echo "SELECT * FROM T1 WHERE f1=?AND f2=? AND f3=?"
java StmtTest6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
