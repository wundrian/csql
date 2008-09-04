#!/bin/sh
# Test Case
# check options -D chunk with empty database
#create table t1 (f1,f2) check with -D chunk

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/catalog
fi

echo "Case 1: With -D chunk option with empty database"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql 
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "Case 2: With -D chunk  option after table creation:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;

