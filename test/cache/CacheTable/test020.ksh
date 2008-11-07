#!/bin/sh

#  Create 't1' table with two records in target DB. \
#  cache t1 from target to csql. 
#  table 't1' can't be deleted by DROP statement.
#  it should be unloaded by -u option

#  AUTHOR : Jitendra Lenka

#!/bin/sh
input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi
rm -f /tmp/csql/csqltable.conf /tmp/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi
echo "cache table 't1' can't be dropped"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
then
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 4;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1

if [ $? -ne 0 ]
then
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 4;
fi

echo "cache table 't1' unloaded by -u option"
rm -f /tmp/csql/csqltable.conf /tmp/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;
