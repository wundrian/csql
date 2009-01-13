#!/bin/sh

#  10.Table there in csql and mysql and not cached. insert should insert only to csql table.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Gateway/csql.conf
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi

isql $DSN < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest10.sql >/dev/null 2>&1 
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/insert.sql
isql $DSN < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
