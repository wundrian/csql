#!/bin/sh
# Donot Start CSQL Server
# Open the connection through jdbc:gateway and then call isClosed(). It should return false.
# Close the connection jdbc:gateway and then call isClosed(). It should return true

# GwTest7.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest7 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;