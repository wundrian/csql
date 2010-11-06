#!/bin/sh
# Create table t1 having two integer field f1 ,f2 with primary key f1 . 
# create table t2 having two integer field f3,f4 with foreign key f3 refers t1 (f1) and a primary key f4
# create table t3 having two integer field f5,f6 with foreign key f5 refers t2 (f4).It Should be passed.
#

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/foreign143.ksh
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t3_t2_t1.sql
   rm -f ${REL_PATH}/drp1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t3_t2_t1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
