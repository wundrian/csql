#!/bin/sh
# Test Case
# 9. Create table t1 in mysql with primary key. Insert 10 rows. 
#    Cache the table in csql. 
#    Update 2 rows in csql and 2 rows in mysql with different primary keys. 
#    Run $ cacheverify -t t1. 
#        The output should display number of records as 10 for both csql and 
#        mysql respectively.
#    Run $ cacheverify -t t1 -p. 
#        The output should display no missing records in either of the 
#        databases.
#    Run $ cacheverify -t t1 -f. 
#        The output should display the 4 inconsistent records. 
#        Only those fields with different values should be displayed 
#        for inconsistent records.   

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/mysqlinput.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

isql myodbc3 < ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/mysqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 2;
fi

isql myodbc3 < ${REL_PATH}/mysqlupdate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 3;
fi


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlupdate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    exit 5;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
    exit 6;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    exit 7;
fi

isql myodbc3 < $REL_PATH/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1

exit 0;
