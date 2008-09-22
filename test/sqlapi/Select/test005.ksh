#!/bin/sh
# Test Case
# check options -D chunk with empty database
#create table t1 (f1,f2) check with -D chunk
#drop t1  check with -D chunk

CSQL_CONF=${PWD}/sqlapi/Select/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/sqlapi/Select
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "Case 1: create table t1 ,test for SET AUTOCOMMIT OFF and some records "
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/create.sql 2>&1 
if [ $? -ne 0 ]
then
   exit 1;
fi

kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;

