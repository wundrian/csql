#!/bin/sh
# Test Case

# 6.load with definition option. should succeed.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

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
ret=0
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 > /dev/null 2>&1
if [ $? -ne 0 ]
then
    ret=1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit $ret;
