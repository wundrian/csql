#!/bin/sh

#  5. Cached table there in csql, but complex query (avg on some field). It should get the correct value from mysql.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Gateway/csql.conf
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

isql $DSN < $REL_PATH/mysqlinputtest5.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<2; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
    echo "Unable to start server"
    exit 1
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/complex.sql
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
