#!/bin/sh
# TEST CASE
#create table t1(f1 int not null,f2 int,f3 int);
#create index idx1 on t1(f1,f2) tree;
#It should be created. 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree6.sql
if [ $? -ne 0 ]
then
    exit 1;
fi
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
    exit 2;
fi
exit 0;
