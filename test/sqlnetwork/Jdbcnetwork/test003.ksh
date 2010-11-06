#!/bin/ksh
# Connect only with connect string "jdbc:csql://localhost:5678/csql" and no username and password. It should fail.
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java -Xms256m -Xmx256m ConnTest3
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
