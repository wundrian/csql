#!/bin/ksh
# Testing limit and offset
# offset tells that from which record you want to fetch
# limit tells that how many records you want to fetch from offset
# offset 0 indicates the 1st record
#
CREATEFILE=${PWD}/sql/Limit/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Limit
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/limit1.sql
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
