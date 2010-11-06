#!/bin/ksh
# Test Case
# check no option, ? 
# check whether authentication is working
#
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/catalog
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: With ? option:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -? 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -?
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

echo "Case 3: With wrong username :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u wronguser -p password 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u wronguser -p password >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
       exit 3;
    fi
fi

echo "Case 4: With wrong password :" 
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p password 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p password >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
       exit 4;
    fi
fi

echo "Case 5: With correct user name  and password :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager
    if [ $? -ne 0 ]
    then
       exit 5;
    fi
fi
