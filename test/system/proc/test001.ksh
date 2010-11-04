#!/bin/ksh
# TestCase:
# check proc slots used and free in proctable
# for i = 1 to 120
#    catalog 
# end for
# check proc slots used and free in proctable
# check if any proc slot holds mutexes
# Note: catalog tool with no option specified connects and disconnects

echo "Case 1: -d option with no connections"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D proc |grep Slots
if [ $? -ne 0 ]
then
   exit 1;
fi


count=120
while [ ${count} -gt 0 ]
do 
  count=`expr ${count} - 1`
    if [ $VALGRIND = "true" ]
    then
        valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog 2> $0.valgr
    else
       $CSQL_INSTALL_ROOT/bin/catalog >/dev/null
       if [ $? -ne 0 ]
       then
           echo "create table failed"
           exit 100;
       fi 
    fi
done
echo "Case 2: -d option after 120 connect/disconnect"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D proc |grep Slots 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D proc |grep Slots
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
exit 0
