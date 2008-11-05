#!/bin/sh

#  1. create table t5. It should be created only in csql and not in mysql5. 

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/csqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/DDL
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
isql $DSN < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/dropall.sql >/dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
