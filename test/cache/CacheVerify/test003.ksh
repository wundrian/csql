#!/bin/sh
# Test Case
# 3. Run cacheverify on a non existing table. 
#    It should give an error saying the table is not present.

$CSQL_INSTALL_ROOT/bin/cacheverify -t not_exists > /dev/null 2>&1
if [ $? -eq 0 ]
then
   exit 1;
fi

exit 0;

