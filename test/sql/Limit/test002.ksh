#!/bin/ksh
# Testing limit and offset on Join.
#
CREATEFILE=${PWD}/sql/Limit/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Limit
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/join.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop2.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop2.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

exit 0;
