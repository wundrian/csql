#!/bin/sh

#  4.insert, select, update, delete on table which is not there in both mysql and csql. All should fail.

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
# edit /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql 2>/dev/null
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 2>/dev/null
isql $DSN < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/select.sql 2>/dev/null
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/update.sql 2>/dev/null
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/delete.sql 2>/dev/null
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 2>/dev/null
isql $DSN < $REL_PATH/selectstar.sql 2>/dev/null
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
