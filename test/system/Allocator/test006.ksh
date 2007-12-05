#!/bin/sh
# TestCase:
# check pages used(normal and merged) and chunks used for user database
# create table t1 with two fields and index on first field
# create index idx1 on t1 (f1)
# check pages used(normal and merged) and chunks used for user database
# drop table t1
# check pages used(normal and merged) and chunks used for user database

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
EXECUTABLE=${PWD}/system/Allocator/create
REL_PATH=.
if [ -s "$EXECUTABLE" ]
then
    REL_PATH=${PWD}/system/Allocator
fi

echo "Case 1: -d option with no table"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 
if [ $? -ne 0 ]
then
   exit 1;
fi

${REL_PATH}/create
if [ $? -ne 0 ]
then
   exit 100;
fi
echo "Tables and Indexes are created"

echo "Case 2: -d option with 1 table"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 
if [ $? -ne 0 ]
then
   exit 1;
fi

${REL_PATH}/drop
if [ $? -ne 0 ]
then
   exit 100;
fi

echo "Case 3: -d option after removing table"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0
