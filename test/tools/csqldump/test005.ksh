#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/tools/csqldump/inputtest005.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/inputtest005.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then 
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump -n 25 
if [ $? -ne 0 ]
then
    exit 2;
fi

cnt=`$CSQL_INSTALL_ROOT/bin/csqldump | grep VALUES | wc -l`

if [ $? -ne 0 -a $cnt -ne 101 ]
then
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    exit 4;
fi

exit 0;
