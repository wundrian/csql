#!/bin/ksh
# Test Case
# Check DDL( create table, drop table, create index, drop index )
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/ddl6.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
