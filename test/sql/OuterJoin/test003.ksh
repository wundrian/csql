#!/bin/ksh
# Testing Left Join on two tables with All Datatypes.
#
CREATEFILE=${PWD}/sql/OuterJoin/dropt1t2.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/OuterJoin
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/leftjoin_t1_t2.sql
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
