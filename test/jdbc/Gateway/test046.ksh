#!/bin/sh
# Donot Start CSQL Server
# Open through "jdbc:gateway", close and then again open through "jdbc:gateway". It should pass.

# GwTest6.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest6 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
