#!/bin/sh

#  3. Create table t1 in CSQL with all supported data types in it. and insert 10 records in it.
#  Note that in this test case the table is not cached in csql and is present in csql
#  insert 10 more records using csql tool.
#  select records with WHERE clause containing parameters for all the fields with different data types.
#  update all fields with WHERE clause on primary key
#  delete records with WHERE clause on all fields

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Gateway/csql.conf
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest3.sql >/dev/null 2>&1 
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 
isql myodbc3 < $REL_PATH/selectstar.sql 2>&1
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest3a.sql >/dev/null 2>&1 
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/select.sql 
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/update.sql >/dev/null 2>&1   
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/delete.sql >/dev/null 2>&1  
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 
isql myodbc3 < $REL_PATH/selectstar.sql 2>&1
isql myodbc3 < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
