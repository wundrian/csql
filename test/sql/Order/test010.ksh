#!/bin/ksh
# Testing Order by on SELF JOINed table. 
#
CREATEFILE=${PWD}/sql/Order/dropemp.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Order
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/table_self.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropemp.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/order_self.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropemp.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropemp.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
