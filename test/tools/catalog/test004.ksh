#!/bin/sh
# Test Case
# create table t1 (f1, f2) , index t1idx1 on t1(f1), index t1idx2 on t1(f2)
# create table t2 (f1, f2) , index t2idx1 on t2(f1)
# insert 10 tuples in both t1 and t2
# Check -T option with table having 1 index
# Check -T option with table having 2 index
# Check -I option on index t1idx2
# drop tables

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
EXECUTABLE=${PWD}/tools/catalog/create
REL_PATH=.
if [ -s "$EXECUTABLE" ]
then
    REL_PATH=${PWD}/tools/catalog
fi

${REL_PATH}/create
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Tables and Indexes are created"
${REL_PATH}/insert
if [ $? -eq 0 ]
then
   exit 1;
fi
echo "Tuples inserted into table"
echo "Case 1: -T option for t1: with two index, with tuples"
$CSQL_INSTALL_ROOT/bin/catalog -u praba -p manager -T t1
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: -T option for t2: with one index, with tuples"
$CSQL_INSTALL_ROOT/bin/catalog -u praba -p manager -T t2
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "Case 3: -I option for idx2 of t1, with tuples"
$CSQL_INSTALL_ROOT/bin/catalog -u praba -p manager -I t1idx2
if [ $? -ne 0 ]
then
   exit 3;
fi

${REL_PATH}/drop
if [ $? -ne 0 ]
then
   exit 100;
fi
echo "Tables and Indexes are dropped"

exit 0
