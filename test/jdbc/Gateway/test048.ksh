#!/bin/sh
# Donot Start CSQL Server
# Test 2000 connections in jdbc:gateway

# GwTest8.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest8 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
