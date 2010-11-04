#!/bin/ksh
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

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
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

isql $DS < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputwithrec.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1 
if [ $? -eq 0 ]
then
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 2;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

