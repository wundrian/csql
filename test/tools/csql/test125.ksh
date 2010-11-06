#!/bin/sh
# Test Case
# Create table t1 having two integer field f1 ,f2 with primary key f1 . create table t2 having two integer field f3,f4 with no primary key exist. and create table t3 having two integer field f5,f6 with foreign key f5 refers t1 (f1) and foreign key f6 refers t2 (f3)..It Should be failed.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

echo "drop table t2;" >${REL_PATH}/drp1.sql
echo "drop table t1;" >>${REL_PATH}/drp1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/foreign8.sql
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
