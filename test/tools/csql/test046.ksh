#!/bin/sh
# TEST CASE
# 1. create table t1 (f1 int not null, f2 int);
# 2. create index idx on t1 (f1) tree unique
# 3. insert duplicate records and it should fail
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
#table creation and insertino of 50 records
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree3.sql 2>/dev/null
if [ $? -ne 0 ]
then
     exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selectstar.sql
if [ $? -ne 0 ]
then
    exit 2;
fi
echo "50 rows selected";
#selecting rows providing condition 
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selcond.sql
if [ $? -ne 0 ]
then
    exit 3;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
    exit 4;
fi
exit 0;
