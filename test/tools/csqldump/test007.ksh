#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
executable=${PWD}/tools/csqldump/insert
REL_PATH=.
if [ -s "$executable" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

$REL_PATH/insert >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >tmp.out
if [ $? -ne 0 ]
then
    exit 2;
fi

head -n 13 tmp.out
tail tmp.out
rm -f tmp.out

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    exit 3;
fi

exit 0;
