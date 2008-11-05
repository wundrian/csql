#!/bin/sh
# Test Case
# 7. For the above scenario, 
#    delete 3 tuples from csql and 
#    delete 2 tuples from mysql. 
#    Run $ cacheverify -t t1.
#        The output should display number of records as 7 and 8 for csql and 
#        mysql respectively.
#    Run $ cacheverify -t t1 -p. 
#        The output should display the primary key field values for missing 
#        records in either of the databases in ascending order.
#    Run $ cacheverify -t t1 -f. 
#        The output should display the records are consistent for the same 
#        primary key.  

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/csqldelete.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/csqldelete.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

isql $DSN < ${REL_PATH}/mysqldelete.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    exit 5;
fi

exit 0;
