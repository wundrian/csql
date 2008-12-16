#!/bin/sh
# Donot Start CSQL Server
# Connect through the csql:gateway URL create Statement and call execute to create a table. it should fail

# GwTest9.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest9 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
