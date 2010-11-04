#!/bin/ksh
#Test Case

#19. create t1 table with some records in TDB,
#    cache it with -c option.
#    Insert some records which satisfy the cache condition into t1 in TDB.
#    Insert some records which do not satisfy cache condition into t1 in TDB.
#    Reload t1 with -r option
#    CSQL should contain all records which satisfies cache condition from TDB

#Run this test only under csql/test or on this directory.
#otherwise, it may fail.

#  AUTHOR : Jitendra Lenka
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

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

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

echo after cahe with -c option
echo "select * from t1"

#select from t1 table
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 3;
fi


isql $DS < ${REL_PATH}/insert.sql >/dev/null 2>&1

# again reload table  with -r option.
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 4;
fi

#after reload, select from t1
echo "after reload , select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 5;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

