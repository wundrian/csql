#!/bin/sh
#Test case
#16. create table t1,t2 in target DB with 10 records.
#    load t1 table with condition option
#    load t2 table with condition .

#    unload the two tables t1,t2 with -u option.

#Run this test only under csql/test or on this derectory.
#otherwise, it mat fail.

#  AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1,t2 in target DB.
isql myodbc3 < ${REL_PATH}/create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "cachetable -t t1"
echo "cachetable -t t2 -c \"t2f1<5\" " 

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
    isql myodbc3 < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db

    exit 2;
fi

echo "Table t1 unloaded from CSQL"

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -c "t2f1<5" >/dev/null 2>&1
if [ $? -ne 0 ]
then
     rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
     touch /tmp/csql/csqltable.conf /tmp/csql/csql.db   
    
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
    exit 3;
fi

# unload the two tables from csql and remove entry from csqltable.conf

echo "Table t2 unloaded from CSQl"
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1
if [ $? -ne 0 ] 
then
     rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
     touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
     isql myodbc3 < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1

     exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -u >/dev/null 2>&1
if [ $? -ne 0 ]
then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
     isql myodbc3 < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
     rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db

     exit 5;
fi
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql myodbc3 <${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;

           
