#!/bin/sh
# Test Case
# check no option, ? 
# check whether authentication is working
#
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/csqldump
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: With ? option:"
$CSQL_INSTALL_ROOT/bin/csqldump -?
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
