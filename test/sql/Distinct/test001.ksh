#!/bin/ksh
# Testing DISTINCT Clause
#
CREATEFILE=${PWD}/sql/Distinct/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Distinct
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/distinct1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
