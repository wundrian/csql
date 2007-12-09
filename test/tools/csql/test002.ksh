#!/bin/sh
# Test Case
# check no option, ? 
# check whether authentication is working
#
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s csql1.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

