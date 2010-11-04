#!/bin/ksh
# Test Case
# Create table t1 in Target DB and insert 1 records in TDB. 
# Set DURABILITY=true and CACHE_TABLE=true in csql.conf. Start csqlserver
# Cache t1 table in SYNC  mode at CSQL 
# Insert 1 record at CSQL.
# It Should be Propagated to TDB.
# Kill The Server
# Set CACHE_TABLE=false in csql.conf. Start csqlserver with same configuration
# The Previous Table Should be Durable here.
# Insert 1 record at CSQL. 
# The Insertion Happens at CSQL should not be propagated to TDB
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
echo SYS_DB_KEY=3399 >> $CSQL_CONFIG_FILE
echo USER_DB_KEY=4499 >> $CSQL_CONFIG_FILE
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DURABILITY=true >>$CSQL_CONFIG_FILE


# CSQL Configuration
rm -rf /tmp/csql
mkdir -p /tmp/csql
mkdir -p /tmp/csql/log
mkdir -p /tmp/csql/db
rm -f /tmp/csql/csqlds.conf /tmp/csql/csqltable.conf
touch /tmp/csql/csqlds.conf /tmp/csql/csqltable.conf
touch /tmp/csql/csqlnw.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

echo INSERTING 1 RECORDS IN TARGET DB
echo "CREATE TABLE t1(f1 int);" >${REL_PATH}/creat_ins_attdb.sql
echo "INSERT INTO t1 values(1);" >>${REL_PATH}/creat_ins_attdb.sql
isql $DS < ${REL_PATH}/creat_ins_attdb.sql
if [ $? -ne 0 ]
    then
        isql $DS < ${REL_PATH}/drop_t1.sql
        exit 1;
fi

isql $DS < ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
    then
        isql $DS < ${REL_PATH}/drop_t1.sql
        rm -rf ${REL_PATH}/creat_ins_attdb.sql
        exit 2;
fi

# RUN CSQL SERVER at CSQL
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 10

echo "CACHING THROUGH SITE1"
echo "cachetable -U root -P manager -t t1"
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1
if [ $? -ne 0 ]
    then
        kill -9 $pid
        ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
        isql $DS < ${REL_PATH}/drop_t1.sql
        rm -rf ${REL_PATH}/creat_ins_attdb.sql
        exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
   rm -rf ${REL_PATH}/creat_ins_attdb.sql
   rm -rf ${REL_PATH}/ins1_atCSQL.sql
 exit 4;
fi

#Insertion in cached table at csql
echo INSERTING 1 RECORD IN CACHED TABLE t1 AT CSQL
echo "INSERT INTO t1 VALUES(2);" >${REL_PATH}/ins1_atCSQL.sql
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/ins1_atCSQL.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
   rm -rf ${REL_PATH}/creat_ins_attdb.sql
   rm -rf ${REL_PATH}/ins1_atCSQL.sql
 exit 5;
fi

echo AFTER INSERT AT CSQL DATA IN CSQL 
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
   rm -rf ${REL_PATH}/creat_ins_attdb.sql
   rm -rf ${REL_PATH}/ins1_atCSQL.sql
 exit 12;
fi

echo AFTER INSERT AT CSQL DATA IN TDB
isql $DS < ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
   rm -rf ${REL_PATH}/creat_ins_attdb.sql
   rm -rf ${REL_PATH}/ins1_atCSQL.sql
 exit 6;
fi

$CSQL_INSTALL_ROOT/bin/csqldump -X >before.sql
kill -9 $pid
ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Cache_table = FALSE"
echo CACHE_TABLE=false >>$CSQL_CONFIG_FILE
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
echo "Server Started"
pid=$!
sleep 2
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump -X >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
    else
        echo Durability Does Not work fine
fi

#Insertion in cached table at csql
echo INSERTING ANOTHER RECORD IN CACHED TABLE t1 AT CSQL
echo "INSERT INTO t1 VALUES(3);" >${REL_PATH}/ins_another_atCSQL.sql
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/ins_another_atCSQL.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1.sql
   rm -f ${REL_PATH}/creat_ins_attdb.sql
   rm -f ${REL_PATH}/ins1_atCSQL.sql
   rm -f ${REL_PATH}/ins_another_atCSQL.sql
 exit 7;
fi

echo AFTER INSERT AT CSQL DATA IN CSQL 
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 -u
   rm -rf ${REL_PATH}/creat_ins_attdb.sql
   rm -rf ${REL_PATH}/ins1_atCSQL.sql
   rm -f ${REL_PATH}/ins_another_atCSQL.sql
 exit 8;
fi

echo AFTER INSERT AT CSQL DATA IN TDB
isql $DS < ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
   isql $DS < ${REL_PATH}/drop_t1.sql
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1.sql
   rm -f ${REL_PATH}/creat_ins_attdb.sql
   rm -f ${REL_PATH}/ins1_atCSQL.sql
   rm -f ${REL_PATH}/ins_another_atCSQL.sql
 exit 9;
fi

echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
if [ $? -ne 0 ]
    then
        kill -9 $pid1
        rm -f before.sql after.sql
        rm -f ${REL_PATH}/creat_ins_attdb.sql
        rm -f ${REL_PATH}/ins1_atCSQL.sql
        rm -f ${REL_PATH}/ins_another_atCSQL.sql
        rm -M 3399 -M 4499 -M 1947 -Q 2525
        exit 10;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1.sql
if [ $? -ne 0 ]
    then
        kill -9 $pid1
        rm -f before.sql after.sql
        rm -f ${REL_PATH}/creat_ins_attdb.sql
        rm -f ${REL_PATH}/ins1_atCSQL.sql
        rm -f ${REL_PATH}/ins_another_atCSQL.sql
        rm -M 3399 -M 4499 -M 1947 -Q 2525
        exit 10;
fi

isql $DS < ${REL_PATH}/drop_t1.sql
if [ $? -ne 0 ]
    then
        kill -9 $pid1
        rm -f before.sql after.sql
        rm -f ${REL_PATH}/creat_ins_attdb.sql
        rm -f ${REL_PATH}/ins1_atCSQL.sql
        rm -f ${REL_PATH}/ins_another_atCSQL.sql
        ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
        exit 11;
fi

rm -f before.sql after.sql
rm -f ${REL_PATH}/creat_ins_attdb.sql
rm -f ${REL_PATH}/ins1_atCSQL.sql
rm -f ${REL_PATH}/ins_another_atCSQL.sql
kill -9 $pid 
ipcrm -M 3399 -M 4499 -M 1947 -Q 2525
exit 0;
