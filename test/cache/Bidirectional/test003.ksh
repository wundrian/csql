#!/bin/sh
# Test Case

# Bi-directional cache  test
# Create two table t1,t1 that has no primary key
# Set bidirectional flag in csql.conf to true,Create log table in the cache and run Trigger 

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi

rm /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

isql $DSN < $REL_PATH/mysqlcreatelogtable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi
 
echo log table created in target db.

isql $DSN < $REL_PATH/create1.sql >/dev/null 2>&1 
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN <$REL_PATH/trigger.sql >/dev/null
isql $DSN <$REL_PATH/trigger1.sql  >/dev/null

for (( a=1; a<3; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5
echo "server  started"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
    exit 2 
fi

isql $DSN < ${REL_PATH}/insert.sql >/dev/null 2>&1
sleep 15
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql >/dev/null 2>&1 

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

kill -2 $pid
ipcrm -M 4000 -M 4500
exit 0;

