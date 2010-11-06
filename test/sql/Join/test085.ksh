#!/bin/ksh
# Testing Left Join on three tables with All Datatypes.
# select t1.f1, t1.f2, t2.f1, t2.f2, t3.f1, t3.f2 from t1 inner join t2 on t1.f1 = t2.f1 inner join t3 on t2.f1 = t3.f1 inner join t1 on t3.f1 = t1.f1;
#
CREATEFILE=${PWD}/sql/Join/dropt1t2.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1_t2_t3.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/inner_t1_t2_t3_t1.sql
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
