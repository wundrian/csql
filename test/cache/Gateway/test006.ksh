#!/bin/sh

#  6. Non cached table there in csql and mysql. run complex query (avg on some field). It should get the correct value from mysql.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Gateway/csql.conf
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/mysqlinputtest5.sql > /dev/null 2>&1

# edit /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/complex.sql

isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
