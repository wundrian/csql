#!/bin/ksh

#  Create table t5. It should be created only in csql and not in TDB

CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/csqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/DDL
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
rm   /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql

isql $DS < $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/dropall.sql >/dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277 -M 1947
exit 0
