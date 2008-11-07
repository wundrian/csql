#!/bin/sh
# Test Case

# 9.create table t1 (f1 int, f2 int) in mysql and 
#   create table t1 (f1 int, f2 int, f3 int) in csql. 
#   load with no definition option. should fail.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
dropAll() {
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
#cp $CSQL_CONFIG_FILE /tmp/csql.conf
#echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
#cp /tmp/csql.conf $CSQL_CONFIG_FILE
}


input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest9.sql > /dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s > /dev/null 2>&1
if [ $? -eq 0 ]
then
    dropAll
cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 1;
fi
dropAll
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;


