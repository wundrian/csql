#!/bin/ksh
# TestCase:
# check pages used(normal and merged) and chunks used for user database
# for i = 1 to 100
#    create table t1 with two fields and index on first field
#    create index idx1 on t1 (f1)
#    drop table t1
# end for
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
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
echo "Tables and Indexes are created"

echo "Case 2: -d option with 1 table"
count=100
while [ ${count} -gt 0 ]
do 
  count=`expr ${count} - 1`
    if [ $VALGRIND = "true" ]
    then
       valgrind --tool=memcheck --leak-check=full ${REL_PATH}/create 2>> $0.valgr
    else
       ${REL_PATH}/create
       if [ $? -ne 0 ]
       then
         echo "create table failed"
         exit 100;
       fi
     fi
     ${REL_PATH}/drop
     if [ $? -ne 0 ]
     then
        echo "drop table failed"
        exit 100;
     fi
done
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
exit 0
