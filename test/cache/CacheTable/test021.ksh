#!/bin/sh
# Test Case

# Create table t4 with f1 int and f2 char,composite primary key (f1,f2) in target database
# Cache it with cachetable tool.
# Insert record to chech weather composite primary key or not.

input=${PWD}/cache/CacheTable/create.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

isql $DSN < ${REL_PATH}/create1.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi
echo table t4 is created with records in target db
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "1:t4 NULL NULL NULL" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
then
    exit 2
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
    exit 3
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert1.sql

if [ $? -ne 0 ]
then
    exit 4
fi

$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t4 -u 
isql $DSN < ${REL_PATH}/drop1.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop1.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0;



