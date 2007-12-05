#!/bin/sh
# TestCase:
# create table with two fields and index on first field
# insert 1000 tuple
# check number of tuples, totalPagesused
# check pagesUsed for storing hash bucket
# check number of index nodes, pagesUsed for storing index nodes
# delete 1000 tuple
# check number of tuples, totalPagesused
# check pagesUsed for storing hash bucket
# check number of index nodes, pagesUsed for storing index nodes

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
EXECUTABLE=${PWD}/system/Allocator/create
REL_PATH=.
if [ -s "$EXECUTABLE" ]
then
    REL_PATH=${PWD}/system/Allocator
fi

${REL_PATH}/create
if [ $? -ne 0 ]
then
   exit 100;
fi
echo "Tables and Indexes are created"
${REL_PATH}/insert1000
echo "Tuples inserted into table"
echo "Case 1: -T option for t1: with 1000 tuple"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: -I option for idx1 of t1, with 1000 tuple"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1
if [ $? -ne 0 ]
then
   exit 2;
fi

${REL_PATH}/delete1000

echo "Tuples deleted from table"
echo "Case 3: -T option for t1: after removing 1000 tuple"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1
if [ $? -ne 0 ]
then
   exit 3;
fi

echo "Case 4: -I option for idx1 of t1, after removing 1000 tuple"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1
if [ $? -ne 0 ]
then
   exit 4;
fi

${REL_PATH}/drop
if [ $? -ne 0 ]
then
   exit 100;
fi
echo "Tables and Indexes are dropped"

exit 0
