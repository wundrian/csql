#!/bin/sh
# Test Case
# 1. Check for help message: $ cachetable -? 

$CSQL_INSTALL_ROOT/bin/cachetable ?
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;

