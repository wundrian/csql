#!/bin/ksh
# Test Case
# Create table t1 in Target DB and insert 5 records in TDB. 
# Cache t1 table using cachetable -t option. 
# Create table t2 at CSQL and insert 5 records.
# Do all DML Operations in both cached as well as non-cached tables.
# Both Cached and Non-Cached tables should be durable, and The data Should be Consistent
# 
CSQL_CONF=${PWD}/cache/Durability/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Durability
fi

rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DURABILITY=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
echo SYS_DB_KEY=2288 >>$CSQL_CONFIG_FILE
echo USER_DB_KEY=3377 >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf /tmp/csql/csqltable.conf
touch /tmp/csql/csqlds.conf /tmp/csql/csqltable.conf

rm -rf /tmp/csql/db/*
mkdir -p /tmp/csql/db

$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

# CSQL Configuration
echo INSERTING 5 RECORDS IN TARGET DB
isql $DS < ${REL_PATH}/create_insert_attdb.sql >/dev/null 2>&1 
if [ $? -ne 0 ]
    then
        isql $DS < ${REL_PATH}/drop_t1.sql
        exit 1;
fi

isql $DS < ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
    then
        isql $DS < ${REL_PATH}/drop_t1.sql
        exit 2;
fi

# RUN CSQL SERVER at site
$CSQL_INSTALL_ROOT/bin/csqlserver > /dev/null 2>&1 &
pid=$!
sleep 10

echo "CACHING THROUGH SITE1"
echo "cachetable -U root -P manager -t t1"
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1
if [ $? -ne 0 ]
    then
        kill -9 $pid
        ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
        isql $DS < ${REL_PATH}/drop_t1.sql
        exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_insert_at_csql.sql
if [ $? -ne 0 ]
    then
        kill -9 $pid
        ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
        isql $DS < ${REL_PATH}/drop_t1.sql
        $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
        exit 4;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 10
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
    else
        echo Durability Does Not work fine
fi
#Insertion in cached table at csql
echo INSERTING 5 RECORDS IN CACHED TABLE t1 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/insert5_atsite1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 5;
fi

echo INSERTING 5 RECORDS AT NON CACHED TABLE t2 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/noncached_insert_t2.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 6;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
echo "Server Killed"
echo ""
echo "Durablity = TRUE"
echo "Server Started" 
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 10 
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
    else
        echo Durability Does Not work fine
fi

#Updation in cached table at csql
echo UPDATING 5 RECORDS IN CACHED TABLE t1 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/update5_atsite1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 7;
fi

echo UPDATING 5 RECORDS AT NON CACHED TABLE t2 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/noncached_update_t2.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 8;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 10
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
    else
        echo Durability Does Not work fine
fi

#Deletion in cached table at csql
echo DELETING 7 RECORDS IN CACHED TABLE t1 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/delete7_atsite1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 9;
fi

echo DELETING 7 RECORDS AT NON CACHED TABLE t2 AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/noncached_delete_t2.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
 exit 10;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 10
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
    else
        echo Durability Does Not work fine
fi

#export CSQL_CONFIG_FILE=/tmp/site/csql.conf
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
if [ $? -ne 0 ]
    then
        kill -9 $pid1
        rm -f before.sql after.sql
        rm -M 2288 -M 3377 -M 1947 -Q 2525
        exit 11;
fi

isql $DS < ${REL_PATH}/drop_t1.sql
if [ $? -ne 0 ]
    then
        kill -9 $pid1
        rm -f before.sql after.sql
        ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
        exit 12;
fi

echo "drop table t2;" >${REL_PATH}/drop_t2.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql

rm -f ${REL_PATH}/drop_t2.sql
rm -f before.sql after.sql
rm -rf /tmp/site
kill -9 $pid 
ipcrm -M 2288 -M 3377 -M 1947 -Q 2525
exit 0;
