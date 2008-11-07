#!/bin/sh
# Test Case
# 4. Create a table t1 with no primary key in mysql. and insert 2 tuples. 
#    Cache the table in csql.
#    Run $ cacheverify -t t1. 
#    It should display number of records for csql and mysql respectively.
#    Run $ cacheverify -t t1 -p. 
#    It should give an error saying no primary key is present on table t1.
#    Run $ cacheverify -t t1 -f. 
#    It should give an error saying no primary key is present on table t1.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/CacheVerify/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

isql $DSN < ${REL_PATH}/inputtest4.sql > /dev/null 2>&1
#$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/inputtest4.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "1:t1 NULL NULL NULL" >/tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -R>/dev/null 2>&1 
if [ $? -ne 0 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p 
if [ $? -eq 0 ]
then
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f 
if [ $? -eq 0 ]
then
    exit 5;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DSN < ${REL_PATH}/drop.sql > /dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1

exit 0;
