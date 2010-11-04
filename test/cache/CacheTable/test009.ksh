#!/bin/ksh
# Test Case

# 9.create table t1 (f1 int, f2 int) in mysql and 
#   create table t1 (f1 int, f2 int, f3 int) in csql. 
#   load with no definition option. should fail.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

dropAll() {
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
}


input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
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

echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo "Inserting table t1 with records in targetDB"
isql $DS < ${REL_PATH}/inputtest4.sql  2>/dev/null

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "Creating the same table t1 in csql without records"
if [ "$DSN" = "oracle" ]
then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest9oracle.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest9.sql
fi
if [ $? -ne 0 ]
then
    dropAll
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    dropAll
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 3;
fi

echo "Caching the table with -s (only load records)"
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s 
if [ $? -ne 0 ]
then
    dropAll
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    dropAll
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 5;
fi

dropAll
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

