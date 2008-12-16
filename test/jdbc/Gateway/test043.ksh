#!/bin/sh
#Donot Start Server .Connect only with connectstring "jdbc:"gateway and no username and password. It should fail

# GwTest3.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest3 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
