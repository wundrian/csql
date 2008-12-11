#!/bin/sh
#Test case
#create table t1(f1 int not null,f2 int,f3 int);
#insert 5 records into t1. Test the following case
#a) update t1 set f1=f1+NULL;
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/null6.sql
if [ $? -ne 0 ]
then
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
    exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/null7.sql
if [ $? -ne 0 ]
then
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
    exit 1;
fi

