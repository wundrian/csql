#!/bin/ksh
# Test Case
# check binary data type table t1 field f1 int ,f2 binary(4)
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
echo "drop table t1;" > ${REL_PATH}/dropp_t1.sql

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/datatype10.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/datatype11.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/datatype12.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 3;
fi
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 4;
fi
rm -f ${REL_PATH}/dropp_t1.sql
exit 0;
