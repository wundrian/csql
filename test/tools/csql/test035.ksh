#!/bin/sh
# Test Case
# 35. Create table (f1 int, f2 int); 
#     Insert 5 tuples (1, 1), (1, 2), (2, 1), (2 ,2), (5, 5). (test035.ksh)
#     create index ind on t1 (f1) unique; 
#     Should fail with unique key violation error.

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/uniqueindontuples.sql 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csqldump -T t1
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

