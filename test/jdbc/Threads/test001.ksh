#!/bin/ksh
#JDBC GATEWAY CACHE 
#no index thread test
TESTFILE=${PWD}/jdbc/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

java noIndexTest 
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   exit 1;
fi
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;
