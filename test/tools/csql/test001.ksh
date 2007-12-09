#!/bin/sh
# Test Case
# check no option, ? 
# check whether authentication is working
#
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/csql <quit.sql
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
$CSQL_INSTALL_ROOT/bin/csql -u wronguser -p password <quit.sql 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 4: With wrong password :" 
$CSQL_INSTALL_ROOT/bin/csql -u root -p password <quit.sql 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 5: With correct user name  and password :"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager <quit.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
