#!/bin/sh
# Test Case
# 6. Create table t1 in mysql with primary key. Insert 10 rows. 
#    Cache the table in csql.
#    Run $ cacheverify -t t1 
#         The output should display the number of records present in csql 
#         and mysql separately.
#    Run $ cacheverify -t t1 -p 
#         The output should display no missing records in either database.
#    Run $ cacheverify -t t1 -f
#         The output should display no missing records and should display 
#                               the data is consistent in both databases.


#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/mysqlinput.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

isql $DSN < ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf


$CSQL_INSTALL_ROOT/bin/cachetable -t t1
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
if [ $? -ne 0 ]
then
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    exit 5;
fi

exit 0;
