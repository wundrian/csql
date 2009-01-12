#!/bin/sh
# Test Case
#create table t2(taking different integer fields) (test034a.ksh)
#create index in various ways.
#Do all operations like select,insert,update,delete on the indexed field.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/indexontuples.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   exit 1;
fi

