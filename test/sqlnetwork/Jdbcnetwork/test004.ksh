#!/bin/ksh
#Connect with connect string "jdbc:sql://localhost:5678/csql" and give correct "user" and "password" in properties object. It should fail.
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest4
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;