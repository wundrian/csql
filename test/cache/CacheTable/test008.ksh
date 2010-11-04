#!/bin/ksh
# Test Case

# 8.load table. csqldump , 
#   unload table csqldump, insert record to mysql directly, 
#   reload table, csqldump and verify the results. 
#   reload should get the inserted record also.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

dropAll() {
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
}

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

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

mv /tmp/csql/csqltable.conf /tmp/csql/csqltable.conf.temp
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqldump 

mv /tmp/csql/csqltable.conf.temp /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u  >/dev/null 2>&1 
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csqldump 

isql $DS < ${REL_PATH}/insert.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqldump 

dropAll

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

