#!/bin/sh
# TEST CASE
# 1. create table t1 (f1 int not null, f2 int);
# 2. create index idx on t1 (f1) tree
# 3. insert duplicate records and it should pass
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree0.sql
if [ $? -ne 0 ]
then
    exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
    exit 2;
fi
exit 0;
