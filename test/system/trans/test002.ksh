#!/bin/ksh
# TestCase:
# check used and free transacation slots in transaction table
# create table
# for i = 1 to 120
#    insert 1 tuple in 1 transaction and abort
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
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/create 2> $0.valgr
else
    ${REL_PATH}/create
    if [ $? -ne 0 ]
    then
      echo "create table failed"
      exit 100;
    fi
fi
echo "Case 1: -d option with no transactions"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi

count=120
while [ ${count} -gt 0 ]
do 
  count=`expr ${count} - 1`
    if [ $VALGRIND = "true" ]
    then
        valgrind --tool=memcheck --leak-check=full ${REL_PATH}/insert1andAbort 2>> $0.valgr
    else
      ${REL_PATH}/insert1andAbort >/tmp/tstlog
      if [ $? -ne 1 ]
      then
        echo "insert failed"
        exit 100;
      fi
    fi
done
echo "Case 2: -d option after 120 aborts"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
${REL_PATH}/drop
if [ $? -ne 0 ]
then
  echo "drop table failed"
  exit 100;
fi
exit 0
