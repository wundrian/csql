#!/bin/sh

# Cache table t1 from target database and drop the table. It should give an error.   

# Run this test only under csql/test or on this directory.
# Otherwise, it may fail

CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/csqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/DDL
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
cp $CSQL_CONFIG_FILE /tmp
echo DSN=$DSN >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/csqlinputtest1.sql >/dev/null
if [ $? -ne 0 ]
then
    echo "unable to creste in target db"
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 1
fi

rm /tmp/csql/csql.db /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then
    echo "unable to cache table from target db"
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    isql $DSN < $REL_PATH/dropall.sql >/dev/null 2>&1
    exit 2 
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/dropall.sql

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
if [ $? -ne 0 ]
then
    echo "unable to Unload the table"
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    isql $DSN < $REL_PATH/dropall.sql >/dev/null 2>&1
    exit 3 
fi
isql $DSN < $REL_PATH/dropall.sql >/dev/null 2>&1
kill -9 $pid  2>/dev/null
ipcrm -M 1199 -M 2277 2>/dev/null
rm /tmp/csql/csql.db /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0
