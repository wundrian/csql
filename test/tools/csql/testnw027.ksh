#!/bin/ksh
# Network Test
# Testing all aggregate functions for all data types 
# The same is present at test129.ksh (without network )
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
echo "drop table t1;" > ${REL_PATH}/dropp_t1.sql

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/aggregate_all_datatype.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/dropp_t1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 3;
fi
rm -f ${REL_PATH}/dropp_t1.sql
exit 0;
