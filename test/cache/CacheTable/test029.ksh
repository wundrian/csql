#!/bin/ksh
#Test Case
# Create table t5 and t6 in target DB 
# Load t5 and t6 table without condition option with direct option
# Insert some record in CSQL tool as csql -g option 
# It should insert into target database not in CSQL database


input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

# create table t1,t2 in target DB.
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
if [ $DSN = "db2" ]
then
    isql $DS < ${REL_PATH}/createt5db2.sql >/dev/null 2>&1
else
    isql $DS < ${REL_PATH}/createt5.sql >/dev/null 2>&1
fi
if [ $? -ne 0 ]
then
   exit 2;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "cachetable -t t5 -D"
echo "cachetable -t t6 -D"

$CSQL_INSTALL_ROOT/bin/cachetable -t t5 -D 
if [ $? -ne 0 ] 
then 
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t6 -D 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    exit 4;
fi

for a in 5 6
do
echo "insert into t$a values(15,20);"
echo "insert into t$a values(16,21);"
done>>${REL_PATH}/insertt5t6.sql

echo  "select query on t1 and t2 table"
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/insertt5t6.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    exit 5;
fi
for a in 5 6
do
echo "select * from t$a;"
done>>${REL_PATH}/selectt5t6.sql

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectt5t6.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 6;
fi
isql $DS < ${REL_PATH}/selectt5t6.sql
$CSQL_INSTALL_ROOT/bin/cachetable -t t6 -u
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 7;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -t t5 -u
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
    rm -f  $REL_PATH/insertt5t6.sql
    rm -f  $REL_PATH/selectt5t6.sql
    exit 8;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop5.sql > /dev/null 2>&1
isql $DS <${REL_PATH}/drop5.sql >/dev/null 2>&1
rm -f  $REL_PATH/insertt5t6.sql
rm -f  $REL_PATH/selectt5t6.sql

exit 0;

