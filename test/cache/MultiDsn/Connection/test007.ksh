#!/bin/ksh
#Test Case

# 7.csqlds.conf fiel has no entries for MySQL and Postgres
#   Default DSN is "psql" is set in the csql.conf file.
   
#   Create table t1 in MyQL and t10 in Postgres.
#   CACHE_TABLE=true in cql.conf file.
#   cache t1 and t10 from respective TDB.
#   It should fail.
#   
#   Author : Jitendra

input=${PWD}/cache/MultiDsn/Connection/mysqltable.sql
REL_PATH=.
if [ -s "$input" ]
then
   REL_PATH=${PWD}/cache/MultiDsn/Connection
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$POSTGRES_DSN >>$CSQL_CONFIG_FILE

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf

#echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DS1 < ${REL_PATH}/mysqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 3;
fi
echo "Table 't1' is created in MySQL."

isql $DS2 < ${REL_PATH}/psqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 4;
fi
echo "Table 't10' is created in Postgres"

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -d $MYSQL_DSN  >/dev/null 2>&1
if [ $? -eq 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 5;
fi
echo "Table 't1' is not cached."

$CSQL_INSTALL_ROOT/bin/cachetable -t t10 >/dev/null 2>&1
if [ $? -eq 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 6;
fi
echo "Table 't10' is not cached."

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
echo "Table 't1' and 't10' is dropped from their respective TDB."

kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;

