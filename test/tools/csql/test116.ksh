#!/bin/sh
# Test Case
# Create table t1 having two integer field f1 ,f2 with primary key f1 .Create table t2 having two integer field f1,f2 with foreign key f1 refers t1 (f1) and Create table t3 having two integer field f1,f2 with foreign key f1 refers t1 (f1). drop FK table t2 but not drop t3.Then drop PK table t1. It should be failed.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

echo "drop table t3;" >${REL_PATH}/drp1.sql
echo "drop table t1;" >>${REL_PATH}/drp1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_fk_pk_fk.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/drp1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/drp1.sql
   exit 2;
fi

rm -f ${REL_PATH}/drp1.sql
exit 0;
