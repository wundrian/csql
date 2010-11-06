#!/bin/sh
# Create table t1 having two integer field f1 ,f2 with primary key f1 . 
# Create table t2 having two integer field f3,f4 with primary key f3 . 
# Create table t3 having two integer field f5,f6 with foreign key f5 refers t1 (f1) and foreign key f6 refers t2 (f3). 
# Drop table t3. Then drop table t1 and t2. It should be Passed 
#

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/foreign146.sql
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
