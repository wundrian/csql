#!/bin/ksh
# Test Case For Testing 'HELP' Command
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
echo "CSQL> HELP;"
$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/help.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
