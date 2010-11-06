#!/bin/ksh
# Test Case
# Checking All Aggregate functions(count,min,max,avg,sum)
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/aggregate6.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
