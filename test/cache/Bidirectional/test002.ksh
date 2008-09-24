#!/bin/sh
# Test Case

# Bi-directional cache  test
# Cache  t1 and t2 table 
# Set bidirectional flag in csql.conf to true,Create log table in target database
#Donot run trigger
input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi

isql myodbc3 < $REL_PATH/mysqlcreatelogtable.sql >/dev/null 2>&1 &
echo  Log table created in target DB

isql myodbc3 < $REL_PATH/create.sql >/dev/null 2>&1 
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql myodbc3 <$REL_PATH/droptrigger.sql >/dev/null

export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

for (( a=1; a<3; a++ ))
do
    echo "1:t$a NULL"
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

isql myodbc3 < ${REL_PATH}/insert.sql >/dev/null 2>&1
sleep 15
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

kill -2 $pid
ipcrm -M 4000 -M 4500
exit 0;

