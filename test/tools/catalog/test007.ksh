#!/bin/sh
# Test Case
# create table t4(f1, f2) primary key on f1
# create table t5 (f1, f2) , primary key on (f1,f2)
# Check -l option on primary flag of the key
# drop tables

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
REL_PATH=.

CSQL_CONF=${PWD}/tools/catalog/csql.conf
input=${PWD}/tools/catalog/create.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/catalog
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
echo "Case 1: create two table t4,t5 "
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createPriFlagTest.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: With -l option after for primary flag checking:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   exit 2;
fi
echo "case 3 : drop two table "
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt4t5.sql

if [ $? -ne 0 ]
then
   exit 4;
fi
echo "t4 ,t5 table droped "
kill -9 $pid
ipcrm -M 1199 -M 2277

exit 0
