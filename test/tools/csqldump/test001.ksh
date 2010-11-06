#!/bin/ksh
# Test Case
# check no option, ? 
# check whether authentication is working
#
echo "Case 1: With no option:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi

echo "Case 2: With ? option:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump -? 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump -?
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

exit 0;
