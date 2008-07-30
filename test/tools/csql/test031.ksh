#!/bin/sh
# Test Case
# check non-unique index with composite keys
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/comp2.sql
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

