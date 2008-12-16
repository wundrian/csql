#!/bin/sh
#Donot Start CSQL Server
#To connect with connectstring "jdbc:gateway" and
#give correct "user" and incorrect "password" in properties object. It should fail.

# GwTest5.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest5 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
