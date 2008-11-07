#!/bin/sh

#  8.Cached table there in csql, but join with another cached table in csql. It should get the correct value from mysql.

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

isql $DSN < $REL_PATH/mysqlinputtest5.sql > /dev/null 2>&1
isql $DSN < $REL_PATH/mysqlinputtest8.sql > /dev/null 2>&1

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<3; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/join.sql

isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;
