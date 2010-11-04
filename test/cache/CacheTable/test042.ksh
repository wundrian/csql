#!/bin/ksh
# Test Case

# Bi-directional cache  test
#     Create table t1 with field create table t1(f1 int unique,f2 char(12),f3 smallint , f4 bigint,primary key(f2));. Make bidirectional flag and cache flag true. Cache the table with cachetable -t t1 -f f1,f3,f4 -p f1 it should pass 

# Author:=bijaya


input=${PWD}/cache/CacheTable/csql1.conf

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql1.conf
cp $REL_PATH/csql1.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql1.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
if [ "$DSN" = "oracle" ]
then  
echo "create table t1(f1 integer unique, f2 char(12), f3 smallint , f4 number(18), primary key(f2));">$REL_PATH/t1.sql
else
echo "create table t1(f1 int unique,f2 char(12),f3 smallint , f4 bigint,primary key(f2));">$REL_PATH/t1.sql
fi
if [ $DSN = "db2" ]
then
    echo "create table t1(f1 int not null unique,f2 char(12) not null,f3 smallint , f4 bigint,primary key(f2));">$REL_PATH/t1.sql
fi
for a in 1 2 3 4 5 6 7 8 9
do
echo "insert into t1 values($a,'papu',12,123124);"
done>>t1.sql
isql $DS < $REL_PATH/t1.sql >/dev/null 2>&1 
if [ $? -ne 0 ]
then
    echo "unable to create in target db"
    rm -f $REL_PATH/t1.sql
    exit 2
fi

echo "drop table t1;">${REL_PATH}/dt1.sql
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "server  started"
if [ $DSN = "oracle" -o "$DSN" = "sybase" -o "$DSN" = "db2" ]
then
  $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -f f1,f3,f4 -p f1 -F
  if [ $? -eq 0 ]
  then
        echo "Table cached test script passed"
        isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
        rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
        kill -9 $pid
        kill `ps -e | grep csqlcacheserver | gawk -F" " '{ print $1 }'`
        ipcrm -M 4000 -M 4500
        exit 0;
   fi
else
    $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -f f1,f3,f4 -p f1
    if [ $? -eq 0 ]
    then
        echo "Table cached test script passed"
        isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
        rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
        kill -9 $pid
        kill `ps -e | grep csqlcacheserver | gawk -F" " '{ print $1 }'`
        ipcrm -M 4000 -M 4500
        exit 0; 
    fi
fi
echo "Table not cached test script failed"
isql $DS <${REL_PATH}/dt1.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
kill `ps -e | grep csqlcacheserver | gawk -F" " '{ print $1 }'`
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 3;

