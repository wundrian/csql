#!/bin/ksh
# Test Case

# 5.create table, load with definition option. should fail.

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
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DS < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinput.sql > /dev/null 2>&1

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
ret=0
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
    ret=1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
   
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit $ret;

