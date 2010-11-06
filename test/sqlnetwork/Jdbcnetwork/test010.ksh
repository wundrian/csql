#!/bin/ksh
# Connect with "jdbc:csql://5678:localhost/csql" and give correct "user" and "password" in properties object. It should fail
TESTFILE=${PWD}/jdbc/Connection/ConnTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Connection
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java ConnTest10
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
