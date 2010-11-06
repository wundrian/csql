#!/bin/sh
# Test Case
# Create table t1 having three integer field f1 ,f2,f3 with composite primary key (f1,f2) and create table t2 having three integer field f1,f2,f3 with foreign key (f1,f3) refers t1 (f1,f2).Insert some record into t1 and insert record into t2 with same value as existing PK table key field. Delete record from t1. it should fail.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

echo "drop table t2;" >${REL_PATH}/drp1.sql
echo "drop table t1;" >>${REL_PATH}/drp1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/foreign3.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp1.sql
   rm -f ${REL_PATH}/drp1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/drp1.sql
   exit 3;
fi

rm -f ${REL_PATH}/drp1.sql
exit 0;
