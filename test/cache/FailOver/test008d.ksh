#!/bin/sh

#  8d. After connect, prepare, execute, CSQL goes down.fetch() should return records from MySQL for cached and MySQL table.
#  fetch() on csql non-cached table will fail.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

CSQL_CONF=${PWD}/cache/FailOver/csql.conf
input=${PWD}/cache/FailOver/csqlinputt3.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/FailOver
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

isql $DSN < $REL_PATH/mysqlinputtest1.sql >/dev/null 2>&1 
echo "table t1(to be cached) inserted into target db"
# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<2; a++ ))
do
    echo "1:t$a"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5
echo "table t1 cached into csql"

isql $DSN < $REL_PATH/mysqlinputtest2.sql >/dev/null 2>&1
echo "table t2(not cached) inserted into target db"
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputt3.sql >/dev/null 2>&1
echo "table t3 inserted into csql db"

$REL_PATH/deleteexeccsqldown &
bgproc=$!
kill -9 $pid 
ipcrm -M 1199 -M 2277
echo "csql server is down"
wait $bgproc
isql $DSN < $REL_PATH/dropall.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;
