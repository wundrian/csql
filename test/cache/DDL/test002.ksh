#!/bin/sh

#  3.recover csql with t1 table
#  create table t1 with csql and it should fail saying table already exists

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/DDL
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

isql $DSN < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
echo "1:t1 NULL NULL NULL" >/tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver -c > /dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql 
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
