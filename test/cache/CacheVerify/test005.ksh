#!/bin/ksh
# Test Case
# 5. Create table t1 with primary key in csql. 
#    Make sure that t1 is not present in mysql and 
#    csqltable.conf file does not have any entry for t1.
#    run $ cacheverify -t t1. 
#    It should give an error saying table t1 is not cached.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/CacheVerify/mysqlinput.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 5 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;
