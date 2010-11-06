#!/bin/ksh
#Connect with connect string "jdbc:csql:lllocalhost:5678/csql" and give correct "user" and "password" in properties object. It should pass.
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest1
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
