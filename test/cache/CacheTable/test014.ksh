#!/bin/ksh
# Test Case
#14. Create 't1' table in Target DB with two records,
#    Load selected records into CSQL with -c "f1=1" option.
#    Select from t1 in csql should display only one record with f1 value 1 

# Author : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi
isql $DS < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

echo Table t1 created with two records in target db.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

#cache from target to csql with -c option
echo "cachetable -t t1 -c \"f1=1\" "
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1=1" >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 2;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;
		
