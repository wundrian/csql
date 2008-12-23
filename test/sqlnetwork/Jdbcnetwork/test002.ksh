#!/bin/sh
#Connect with connect string "jdbc:csql:lllocalhost:5678/csql" and null for username and password. It should fail.
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest2
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
