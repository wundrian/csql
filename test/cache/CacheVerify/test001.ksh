#!/bin/sh
# Test Case
# 1. Check for help message: $ cacheverify -? 

$CSQL_INSTALL_ROOT/bin/cacheverify ?
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;

