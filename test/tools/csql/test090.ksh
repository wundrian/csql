#!/bin/sh
# Test Case
# create table t1(f1 int,f2 int,f3 int,primary key(f1,f2));
# insert duplicate values in composite key field. It should be failed.
# create table t1(f1 int,f2 int,f3 int,primary key(f1,f3));
# insert duplicate values in composite key field. It should be failed.
# create table t1(f1 int,f2 int,f3 int,f4 int,primary key(f2,f4));
# insert duplicate values in composite key field. It should be failed.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/composite1.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/composite2.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/composite3.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
