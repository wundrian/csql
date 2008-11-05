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

# write to csqltable.conf file
echo "1:t1 NULL" > /tmp/csql/csqltable.conf
echo "2:t2 t2f1<5" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    isql $DSN < ${REL_PATH}/dropall.sql >/dev/null 2>&1
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt3.sql 2>&1 >/dev/null 

$CSQL_INSTALL_ROOT/bin/cachetable -t t3 -u 
if [ $? -eq 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    isql $DSN < ${REL_PATH}/dropall.sql >/dev/null 2>&1
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
    exit 2;
fi

rm /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < ${REL_PATH}/dropall.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
exit 0;

