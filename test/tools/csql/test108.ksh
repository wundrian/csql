#!/bin/sh
# Test Case
# Create table t1 having two integer field f1 ,f2 with primary key f1 and create table t2 having two integer field f1,f2 with foreign key f1 refers t1 (f1). Insert some record into t1 and insert record into t2 with same value as existing PK table key field.It should pass.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi


echo "drop table t2;" >${REL_PATH}/drp1.sql
echo "drop table t1;" >>${REL_PATH}/drp1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_parent_child.sql
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
   exit 2;
fi

rm -f ${REL_PATH}/drp1.sql
exit 0;
