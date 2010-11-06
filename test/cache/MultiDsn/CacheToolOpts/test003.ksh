#!/bin/ksh

#  1. Create 2 tables in each of the TDB in
#     MySQL, Postgres,DB2 and Oracle.

#  Default DSN is set as "myodbc3".
#  Use "cachetable tool" to cache the tables from DSNs 
#    in a range of MySQL,Postgres,DB2 and Oracle.

#  Use "cachetable -d <dsnName>" to cache all the tables from a specific DSN.

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

$CSQL_INSTALL_ROOT/bin/csqlds -U $DB2_USER -P $DB2_PASSWORD -D $DB2_DSN -N $DB2_TDB -a
if [ $? -ne 0 ]
then
   exit 3;
fi
echo "Entries made for $DB2_DSN in csqlds.conf file."

$CSQL_INSTALL_ROOT/bin/csqlds -U $ORACLE_USER -P $ORACLE_PASSWORD -D $ORACLE_DSN -N $ORACLE_TDB -a
if [ $? -ne 0 ]
then
   exit 4;
fi
echo "Entries made for $ORACLE_DSN in csqlds.conf file."

#drop teh table in all DSN if exists.
isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1
 
 
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

isql $DS3 < ${REL_PATH}/db2table.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 7;
fi
echo "Table 't5 and t6' is created in $DB2_DSN"

isql $DS4 < ${REL_PATH}/oracletable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 8;
fi
echo "Table 't7 and t8' is created in $ORACLE_DSN"


rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# Start teh csql server.
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
        
      #### cache all the table from DSNs #####
echo " "
echo "Table from MySQL"
$CSQL_INSTALL_ROOT/bin/cachetable  -d $MYSQL_DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 9;
fi
sleep 2

echo " "
echo "Tables from Postgres"
$CSQL_INSTALL_ROOT/bin/cachetable -d $POSTGRES_DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 10;
fi
sleep 2

echo " "
echo "Tables from DB2"
$CSQL_INSTALL_ROOT/bin/cachetable -d $DB2_DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 11;
fi
sleep 2

echo " "
echo "Tables from Oracle"
$CSQL_INSTALL_ROOT/bin/cachetable -d $ORACLE_DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 12;
fi
sleep 2

      #### Now use "cachetable -l <dsName>" ####

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/showtables.sql

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf

isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS4 < ${REL_PATH}/drop.sql >/dev/null 2>&1


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;


