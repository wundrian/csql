#!/bin/sh
#Test case
#create table t1( f1 int not null,f2 int, f3 int);
#a) create tree unique index on first field
#b) create tree primary index on same firld.
#It should be failed Saying "Index on this field already exists". 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree17.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csqldump -T t1
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

