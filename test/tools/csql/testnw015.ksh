#!/bin/ksh
# Test Case
# check all Predicates with BIGINT (long long) data type
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/datatype7.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
