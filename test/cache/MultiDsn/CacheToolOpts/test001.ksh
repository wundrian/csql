#!/bin/ksh

#  1. Create 2 tables in each of the TDB in
#     MySQL, Postgres,DB2 and Oracle.

#  Default DSN is set as "myodbc3".
#  Use "cachetable tool" to cache teh tables from DSNs.
#  Use "cachetable -l <dsnName>" to get the cached tables
#  present in the specified DSN.   

#  Run this test only under cql/test or on this directory,
#  Otherwise it will fail.


input=${PWD}/cache/MultiDsn/CacheToolOptions/mysqltable.sql
REL_PATH=.
if [ -s "$input" ]
then
  REL_PATH=${PWD}/cache/MultiDsn/CacheToolOptions
fi

rm -f /tmp/csql.conf
cp -f $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$MYSQL_DSN >>$CSQL_CONFIG_FILE

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf


      ##########  csqlds.conf entries  #########

$CSQL_INSTALL_ROOT/bin/csqlds -U $MYSQL_USER -P $MYSQL_PASSWORD -D $MYSQL_DSN -N $MYSQL_TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Entries made for $MYSQL_DSN  in csqlds.conf file."

$CSQL_INSTALL_ROOT/bin/csqlds -U $POSTGRES_USER -P $POSTGRES_PASSWORD -D $POSTGRES_DSN -N $POSTGRES_TDB -a
if [ $? -ne 0 ]
then
   exit 2;
fi
echo "Entries made for $POSTGRES_DSN in csqlds.conf file."

#drop teh table in all DSN if exists.
isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
 
 
       ####### Craete Table in all DSN #######

isql $DS1 < ${REL_PATH}/mysqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 5;
fi
echo "Table 't1 and t2' is created in $MYSQL_DSN"

isql $DS2 < ${REL_PATH}/psqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 6;
fi
echo "Table 't3 and t4' is created in $POSTGRES_DSN"

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# Start teh csql server.
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
        
      #### cache all the table from DSNs #####
for a in 1 2 
do
    $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $MYSQL_DSN
    if [ $? -ne 0 ]
    then
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
       isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
       exit 7;
    fi
    sleep 2
done

for a in 3 4
do
    $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $POSTGRES_DSN
    if [ $? -ne 0 ]
    then
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
       isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
       exit 8;
    fi
    sleep 2
done
   
      #### Now use "cachetable -l <dsName>" ####

echo "Tables in $MYSQL_DSN"
$CSQL_INSTALL_ROOT/bin/cachetable -l $MYSQL_DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 9;
fi

echo "Tables in $POSTGRES_DSN"
$CSQL_INSTALL_ROOT/bin/cachetable -l $POSTGRES_DSN
if [ $? -ne 0 ]
then
    kill -9 $pid
    ipcrm -M 1199 -M 2277
    isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 10;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf

isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;


