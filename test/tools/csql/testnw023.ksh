#!/bin/ksh
# Test Case
#create table t2(taking different integer fields)
#create index in various ways.
#Do all operations like select,insert,update,delete on the indexed field.
#

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/diffintindex.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/drop.sql
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi
exit 0;
