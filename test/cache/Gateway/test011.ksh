#!/bin/ksh

#  11.Table there in csql and mysql and not cached. select should return records in csql table.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm -f /tmp/csql.conf

cp $REL_PATH/csql.conf /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

if [ $DSN = "oracle" ]
then
   isql $DS < $REL_PATH/orainputt1.oracle >/dev/null 2>&1
elif [ $DSN = "sybase" ]
then
   isql $DS < $REL_PATH/sybaseinputtest1.sql >/dev/null 2>&1
elif [ $DSN = "db2" ]
then
   isql $DS < $REL_PATH/db2inputtest1.sql >/dev/null 2>&1
else
   isql $DS < $REL_PATH/mysqlinputtest1.sql >/dev/null 2>&1
fi

if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi

isql $DS < $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

if [ $DSN = "oracle" ]
then
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/orainputt1.oracle  >/dev/null 2>&1
else
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest10.sql >/dev/null 2>&1
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
isql $DSN < $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;
