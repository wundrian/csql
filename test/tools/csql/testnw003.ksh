#!/bin/ksh
# Test Case
# Creating table with not null constraint and primary key constraint on the int field
# check basic UPDATE and DELETE
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/csql2.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
