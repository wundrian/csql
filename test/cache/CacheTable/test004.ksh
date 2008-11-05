#!/bin/sh
# Test Case

# 4.create table, insert some records into the table and then load with no definition option. should fail.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

isql $DSN < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputwithrec.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1 
if [ $? -eq 0 ]
then
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    exit 2;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1

exit 0;

