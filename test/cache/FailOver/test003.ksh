#!/bin/sh

#  3. SELECT/INSERT/UPDATE/DELETE on MySQL table, when csqlserver is down should pass.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

CSQL_CONF=${PWD}/cache/FailOver/csql.conf
input=${PWD}/cache/FailOver/csqlinput.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/FailOver
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/mysqlinputtest1.sql >/dev/null 2>&1 
echo "table t1 inserted into target db"
# edit /tmp/csql/csqltable.conf
echo "csql server is down"
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinput.sql

isql $DSN < $REL_PATH/dropall.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;
