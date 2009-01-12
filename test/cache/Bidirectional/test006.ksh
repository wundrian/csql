#!/bin/sh
# Test Case

# Bi-directional cache  test
# Cache t1 and t2 table with primary key field
# Set bidirectional flag in csql.conf to true,Create log table from target db .Run trigger.

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
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo ENABLE_BIDIRECTIONAL_CACHE=true >>$CSQL_CONFIG_FILE

isql $DSN < $REL_PATH/mysqlcreatelogtable.sql >/dev/null 2>&1 &
echo Log table created in target DB

isql $DSN < $REL_PATH/create.sql >/dev/null 2>&1 
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
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql 
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    exit 1 
fi
echo "Update some record in target database"
isql $DSN < ${REL_PATH}/update.sql >/dev/null 2>&1
sleep 15 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < $REL_PATH/mysqldeletelogtable.sql >/dev/null 2>&1 
kill -2 $pid
ipcrm -M 4000 -M 4500
exit 0;

