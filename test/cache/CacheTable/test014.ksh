#!/bin/sh
# Test Case
#14. Create 't1' table in Target DB with two records,
#    Load selected records into CSQL with -c "f1=1" option.
#    select query executes the selected records from CSQL.

#Run this only under csql/test or on this directory, Otherwise it will fail.  

# Author : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

isql $DSN < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi

echo Table t1 created with two records in target db.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

#cache from target to csql with -c option
echo "cachetable -t t1 -c \"f1=1\" "
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1=1" >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 2;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1

exit 0;
		
