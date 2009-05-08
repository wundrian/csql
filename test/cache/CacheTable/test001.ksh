#!/bin/sh
# Test Case
# 1. Check for help message: $ cachetable -? 
cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
$CSQL_INSTALL_ROOT/bin/cachetable ?
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;

