#!/bin/ksh
# Testing DISTINCT by applying inner Join on  two tables with all datatypes .
#
CREATEFILE=${PWD}/sql/Distinct/drop_t1_t2_t3.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Distinct
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype_t1_t2_t3.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/distinct_alltypes_innerjoin.sql
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
