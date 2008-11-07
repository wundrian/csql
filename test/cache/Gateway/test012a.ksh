#!/bin/sh

#  12.csqlserver not running
#  a)connect,select
#  oncached table in mysql(should work), cached table (work), csql table (fail)

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

isql $DSN < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1
isql $DSN < $REL_PATH/mysqlinputtest12.sql > /dev/null 2>&1

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
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest12.sql >/dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart2.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart3.sql
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;
