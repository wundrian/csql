#!/bin/ksh
# Testing Order by applying INNER JOIN and LEFT JOIN on multiple tables . 
# This script is also for testing all the keywords supported for select query.
#
CREATEFILE=${PWD}/sql/Order/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Order
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/table_t1_t2_t3.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/order_inner_left.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
