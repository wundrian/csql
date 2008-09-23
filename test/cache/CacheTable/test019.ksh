#!/bin/sh
#Test Case

#19. create t1 table with some records in target DB,
#    cache it with -c option.
#    Again add some more record into t1 which is in target DB.
#    now cache it with -r option
#    it will reload the table t1 in CSQL  with latest record.

#Run this test only under csql/test or on this directory.
#otherwise, it may fail.

#  AUTHOR : Jitendra Lenka
input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

isql myodbc3 < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1=1" >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 2;
fi

echo after cahe with -c option
echo "select * from t1"

#select from t1 table
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 3;
fi


isql myodbc3 < ${REL_PATH}/insert.sql >/dev/null 2>&1

# again reload table  with -r option.
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 4;
fi

#after reload, select from t1
echo "after reload , select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 5;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;

