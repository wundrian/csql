#!/bin/ksh
# Testing Join on 5 sales tables.
# Create 5 tables like client_master,product_master,salesman_master,sales_order,sales_order_details.
# populate the above tables with required values.
# List the products which have been sold to 'Ivan Bayross'
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_tables.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_join.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
exit 0;
