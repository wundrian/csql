#!/bin/sh
# Test Case

# 10. Create table t1 with primary key in csql and insert 10 tuples. 
#     Create the same table in mysql and add 10 tuples with different 
#     primary key values.
#     Add entry for table t1 in csqltable.conf file. 
#     Now run $ csqlverify -t t1 -p. 
#     The output should be displayed without any error.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/mysqlinput.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

isql myodbc3 < ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinput.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 2;
fi

echo "1:t1" > /tmp/csql/csqltable.conf

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

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
isql myodbc3 < $REL_PATH/drop.sql >/dev/null 2>&1

exit 0;
