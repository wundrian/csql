#!/bin/ksh
#Test Case

#18. load t1 table with records in target DB,
#    create a t1 table in CSQL without record. 
#    load with -s option, it should pass.

#   AUTHOR : Jitendra Lenka

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
if [ "$DSN" = "oracle" ]
then 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/csqlinputoracle.sql > /dev/null 2>&1 
else
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/csqlinput.sql > /dev/null 2>&1
fi
if [ $? -ne 0 ]
then
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 2;
fi
  
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# caching with -s option
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 3;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selectt1.sql 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 4;
fi
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;
