#!/bin/sh
# Test Case
# check binary data type table t1 field f1 int ,f2 binary(4),primary key(f2)
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/datatype12.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
