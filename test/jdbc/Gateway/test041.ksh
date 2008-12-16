#!/bin/sh
# Connect with connectstring "jdbc:gateway" and give correct "user" and "password" in properties object.
# It should pass.when csqlserver is not runnig
# GwTest1.java

TESTFILE=${PWD}/jdbc/Gateway/GwTest1.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
java GwTest1 
if [ $? -ne 0 ]
then
   exit 1;
fi


exit 0;
