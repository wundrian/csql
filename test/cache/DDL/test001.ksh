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
rm  /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE
echo CACHE_TABLE=true >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/dropall.sql >/dev/null
rm /tmp/csql/csql.db /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
isql $DSN < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/dropall.sql >/dev/null 2>&1
kill -s SIGTERM $pid  2>/dev/null
ipcrm -M 1199 -M 2277 2>/dev/null
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0
