#!/bin/ksh
# Test Case
# Predicate test  
# Is NULL and In Not NULL test
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
$CSQL_INSTALL_ROOT/bin/csql  < ${REL_PATH}/isNullNotNull.sql 
if [ $? -ne 0 ]
then
   echo passed
   exit 1;
fi
exit 0;
