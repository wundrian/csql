#!/bin/sh
#Test Case
# Create table t5 and t6 in target DB 
# Load t5 and t6 table without condition option with direct option
# Insert some record in CSQL tool as csql -g option it should insert into targert database not in CSQL database


input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1,t2 in target DB.
isql myodbc3 < ${REL_PATH}/createt5.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "cachetable -t t5 -D"
echo "cachetable -t t6 -D"

$CSQL_INSTALL_ROOT/bin/cachetable -t t5 -D 
if [ $? -ne 0 ] 
then 
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t6 -D 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    exit 3;
fi

for((a=5;a<=6;a++))
do
echo "insert into t$a values(15,20);"
echo "insert into t$a values(16,21);"
done>>${REL_PATH}/insertt5t6.sql

echo  "select query on t1 and t2 table"
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/insertt5t6.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    exit 4;
fi
for((a=5;a<=6;a++))
do
echo "select * from t$a;"
done>>${REL_PATH}/selectt5t6.sql

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectt5t6.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 4;
fi
isql myodbc3 < ${REL_PATH}/selectt5t6.sql
$CSQL_INSTALL_ROOT/bin/cachetable -t t6 -u
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 5;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -t t5 -u
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 6;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop5.sql > /dev/null 2>&1
isql myodbc3 <${REL_PATH}/drop5.sql >/dev/null 2>&1
rm -f  $REL_PATH/insertt5t6.sql
rm -f  $REL_PATH/selectt5t6.sql

exit 0;











