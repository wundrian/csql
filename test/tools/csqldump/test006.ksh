#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/tools/csqldump/inputtest006.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/inputtest006.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then 
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump
if [ $? -ne 0 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    exit 3;
fi

exit 0;
