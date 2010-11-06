#!/bin/ksh
#Connect with connectstring "jdbc:csql://localhost:5678/csql" and give incorrect "user" and "password" in properties object. It should fail.
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest6
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
