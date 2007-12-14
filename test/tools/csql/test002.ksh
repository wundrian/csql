#!/bin/sh
# Test Case
# check basic INSERT, SELECT
#
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s csql1.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

