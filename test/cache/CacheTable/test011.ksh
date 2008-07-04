#!/bin/sh
# Test Case

# 9.create table t1 (f1 int, f2 int) in mysql and 
#   create table t1 (f1 int, f2 int, f3 int) in csql. 
#   load with no definition option. should fail.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/CacheTable/create.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

isql myodbc3 < ${REL_PATH}/create.sql >/dev/null 2>&1
echo table t1 and t2 are created with records in target db

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<3; a++ ))
do
    echo "1:t$a"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u 
if [ $? -ne 0 ]
then
    exit 2;
fi
echo table t1 unloaded
$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -u 
if [ $? -ne 0 ]
then
    exit 3;
fi
echo table t2 unloaded
grep t1 /tmp/csql/csqltable.conf
if [ $? -eq 0 ]
then 
    exit 4;
fi

grep t2 /tmp/csql/csqltable.conf
if [ $? -eq 0 ]
then 
    exit 5;
fi

isql myodbc3 < ${REL_PATH}/dropall.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
exit 0;

