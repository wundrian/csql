#!/bin/sh
# TestCase:
# check used and free transacation slots in transaction table
# create table
# for i = 1 to 120
#    insert 1 tuple in 1 transaction and commit
# end for
# check used and free transacation slots in transaction table

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
EXECUTABLE=${PWD}/system/trans/create
REL_PATH=.
if [ -s "$EXECUTABLE" ]
then
    REL_PATH=${PWD}/system/trans
fi
${REL_PATH}/create
if [ $? -ne 0 ]
then
  echo "create table failed"
  exit 100;
fi

echo "Case 1: -d option with no transactions"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans
if [ $? -ne 0 ]
then
   exit 1;
fi


count=120
while [ ${count} -gt 0 ]
do 
  count=`expr ${count} - 1`
  ${REL_PATH}/insert1andCommit >/tmp/tstlog
  if [ $? -ne 1 ]
  then
    echo "insert failed"
    exit 100;
  fi
done
echo "Case 2: -d option after 120 commits"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans
if [ $? -ne 0 ]
then
   exit 1;
fi
${REL_PATH}/drop
if [ $? -ne 0 ]
then
  echo "drop table failed"
  exit 100;
fi
exit 0
