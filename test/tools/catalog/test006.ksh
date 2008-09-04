#!/bin/sh
# Test Case
#create table t2 (f1,f2,f3) ,with primary key(f1) and index on f3 .check with -D chunk 
#insert 20 tuples and check with -D chunk
#delete 10 tuples and check with -D chunk
#drop t1 and t2 check with -D chunk

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/catalog
fi


$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create1.sql 
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Table  created"

echo "Case 1: With -D chunk  option after table creation:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert.sql 
if [ $? -ne 0 ]
then
   exit 3;
fi
echo "Tuples insered"
echo "Case 2: With -D chunk  option after insert 20 tuples:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 4;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/delete.sql 
if [ $? -ne 0 ]
then
   exit 5;
fi

echo "10 tuples deleted"

echo "Case 3: With -D chunk option after deleting 10 tuples :"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 6;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropIndex.sql 
if [ $? -ne 0 ]
then
   exit 7;
fi
echo "Index droped"

echo "Case 4: With -D chunk  option after Index droped :"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 8;
fi;

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql 

if [ $? -ne 0 ]
then
   exit 9;
fi
echo "t1,t2 table droped with index"

echo "Case 5: With -D chunk  option after drop t1,t2 :"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
if [ $? -ne 0 ]
then
   exit 10;
fi

exit 0;
