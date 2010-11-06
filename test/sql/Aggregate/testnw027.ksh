#!/bin/ksh
# Testing Join on 5 sales tables.
# Create 5 tables like client_master,product_master,salesman_master,sales_order,sales_order_details.
# populate the above tables with required values.
# Test join, aggregate and having on them by executing the following query:
# List the productno,Description and their quantities for the orders placed by 'Ivan Bayross' and Mamta Muzumdar'  
#
QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/sales_tables.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/sales_join_aggregate2.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sales_table_drop.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
