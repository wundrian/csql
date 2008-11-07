#!/bin/sh
# Test Case

# Create table t5 with f1 int unique and f2 int,primary key (f2) in target database
# Cache it with cachetable tool.
# Check with catalog -D chunk tool weather index is created for both primary as well as unique.

input=${PWD}/cache/CacheTable/createt5.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/createt5.sql >/dev/null 2>&1
echo table t5 is created with records in target db

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csqlserver  >/dev/null 2>&1 &
pid=$!
sleep 5
echo "1:t5 NULL NULL NULL" >> /tmp/csql/csqltable.conf
echo "1:t6 NULL NULL NULL" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
    exit 3;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t5 -u
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t6 -u
isql $DSN < ${REL_PATH}/drop5.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0;

