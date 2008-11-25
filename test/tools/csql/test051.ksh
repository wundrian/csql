#!/bin/sh
# TEST CASE
#create table t1(f1 int not null,f2 int,f3 int);
#create multiple tree index on the same table by taking different combination of fields
#create index idx1 on t1(f1) tree;
#create index idx2 on t1(f2) tree;
#create index idx3 on t1(f3) tree;
#create index idx4 on t1(f1,f2) tree;
#create index idx5 on t1(f2,f3) tree;
#create index idx6 on t1(f3,f1) tree;
#create index idx7 on t1(f1,f2,f3) tree;
#all should work fine. 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree7.sql
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
