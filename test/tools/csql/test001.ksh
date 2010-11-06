#!/bin/ksh
# Test Case
# check no option, ? 
# check whether authentication is working
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/csql < ${REL_PATH}/quit.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Case 2: With ? option:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -? 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -? 
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

echo "Case 3: With wrong username and wrong password :" 
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u wronguser -p password < ${REL_PATH}/quit.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u wronguser -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
       echo passed
       exit 3;
    fi
fi
echo failed

echo "Case 4: With wrong username :" 
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u wronguser -p manager < ${REL_PATH}/quit.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u wronguser -p manager < ${REL_PATH}/quit.sql >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
       echo Passed 
       exit 4;
    fi
fi
echo Failed

echo "Case 5: With wrong password :" 
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p password < ${REL_PATH}/quit.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
       echo passed
       exit 5;
    fi
fi
echo failed

echo "Case 6: With correct user name  and password :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager < ${REL_PATH}/quit.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager < ${REL_PATH}/quit.sql
    if [ $? -ne 0 ]
    then
       echo failed 
       exit 6;
    fi
fi

echo passed
