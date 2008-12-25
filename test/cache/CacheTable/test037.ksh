#!/bin/sh
# Test Case

# Bi-directional cache  test
# Create table t1 with field f1 int ,f2 char,f3 smallint , f4 bigint . Make bidirectional flag and cache flag true. Cache the table with cachetable -t t1 -f f1,f2,f3 -p f1 it should pass

# Author:=bijaya


input=${PWD}/cache/CacheTable/csql1.conf

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql1.conf
cp $CSQL_CONFIG_FILE /tmp/csql1.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
echo "create table t1(f1 int ,f2 char(12),f3 smallint , f4 bigint);">$REL_PATH/t1.sql
for((a=1;a<10;a++))
do
echo "insert into t1 values($a,'papu',12,$a+123124);"
done>>t1.sql
isql $DSN < $REL_PATH/t1.sql >/dev/null 2>&1 
if [ $? -ne 0 ]
then
    echo "unable to creste in target db"
    rm -f $REL_PATH/t1.sql
    cp /tmp/csql1.conf $CSQL_CONFIG_FILE
    exit 1
fi

echo "drop table t1;">${REL_PATH}/dt1.sql
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "server  started"
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -p f1
if [ $? -ne 0 ]
then
    echo "Unable to cache"
    isql $DSN <${REL_PATH}/dt1.sql  >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
    cp /tmp/csql1.conf $CSQL_CONFIG_FILE
    kill -2 $pid
    ipcrm -M 4000 -M 4500
    exit 2 
fi
isql $DSN <${REL_PATH}/dt1.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
kill -2 $pid
ipcrm -M 4000 -M 4500
cp /tmp/csql1.conf $CSQL_CONFIG_FILE
exit 0;

