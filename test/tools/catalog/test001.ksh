#!/bin/sh
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
$CSQL_INSTALL_ROOT/bin/catalog -?
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 3: With wrong username :"
$CSQL_INSTALL_ROOT/bin/catalog -u wronguser -p password 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 4: With wrong password :" 
$CSQL_INSTALL_ROOT/bin/catalog -u praba -p password 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 1;
fi

echo "Case 5: With correct user name  and password :"
$CSQL_INSTALL_ROOT/bin/catalog -u praba -p manager
if [ $? -ne 0 ]
then
   exit 1;
fi
