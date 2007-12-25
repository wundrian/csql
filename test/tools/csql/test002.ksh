#!/bin/sh
# Test Case
# check basic INSERT, SELECT
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/csql1.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
