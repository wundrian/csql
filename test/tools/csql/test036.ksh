#!/bin/sh
# Test Case
# 36. Create table t1 with composite primary key. 
#     t1(f1 int, f2 int, primary key(f1, f2)); 
#     create one more index indx on t1(f1). 
#     the index should be created.

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/singleandcompind.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l 
if [ $? -ne 0 ]
then
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi
exit 0;	
