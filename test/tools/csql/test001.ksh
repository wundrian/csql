#!/bin/sh
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
$CSQL_INSTALL_ROOT/bin/csql -? 
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 3: With wrong username :" 
$CSQL_INSTALL_ROOT/bin/csql -u wronguser -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 4: With wrong password :" 
$CSQL_INSTALL_ROOT/bin/csql -u root -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 5: With correct user name  and password :"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager < ${REL_PATH}/quit.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
