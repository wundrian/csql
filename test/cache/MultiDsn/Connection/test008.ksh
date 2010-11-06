#!/bin/ksh
#Test Case

# 8.csqlds.conf file has the entries for MySQL and Postgres
#   Default DSN is "psql" in csql.conf file.

# Create table t1 in MyQL and t10 in Postgres.
# CACHE_TABLE=false in csql.conf file.
# cache t1 and t10 from their respective TDB.
#
# Author : Jitendra

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

$CSQL_INSTALL_ROOT/bin/csqlds -U $MYSQL_USER -P $MYSQL_PASSWORD -D $MYSQL_DSN -N $MYSQL_TDB -a
if [ $? -ne 0 ]
then 
   exit 1;
fi
echo "Entries made for $MYSQL_DSN in csqlds.conf file."

$CSQL_INSTALL_ROOT/bin/csqlds -U $POSTGRES_USER -P $POSTGRES_PASSWORD -D $POSTGRES_DSN -N $POSTGRES_TDB -a
if [ $? -ne 0 ]
then
   exit 2;
fi
echo "Entries made for $POSTGRES_DSN in csqlds.conf file."

echo CACHE_TABLE=false >>$CSQL_CONFIG_FILE
echo "CACHE_TABLE=false in csql.conf file."

isql $DS1 < ${REL_PATH}/mysqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 3;
fi
echo "Table 't1' is created in $MYSQL_DSN."

isql $DS2 < ${REL_PATH}/psqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 4;
fi
echo "Table 't10' is created is $POSTGRES_DSN."

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
echo "CSQL Server started."

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -d $POSTGRES_DSN >/dev/null 2>&1
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

