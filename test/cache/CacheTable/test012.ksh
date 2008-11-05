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

isql $DSN < ${REL_PATH}/create.sql >/dev/null 2>&1
echo table t1 and t2 are created with records in target db

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

# write to the csqltable.conf file
echo "1:t1 NULL" > /tmp/csql/csqltable.conf
echo "2:t2 t2f1>5" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/deletefromt1csql.sql 
isql $DSN < $REL_PATH/deletefromt2mysql.sql

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r 
if [ $? -ne 0 ]
then
    exit 2;
fi
echo table t1 reloaded
$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -r 
if [ $? -ne 0 ]
then
    exit 3;
fi
echo table t2 reloaded

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < ${REL_PATH}/dropall.sql >/dev/null 2>&
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
exit 0;

