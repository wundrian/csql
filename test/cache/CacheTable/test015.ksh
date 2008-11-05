#!/bin/sh
#Test Case
#15. create table t1 and t2 in target DB with 10 records
#    Load t1 table without condition option
#    Load t2 with condition " t2f1 < 5 ". 

#    table t1 should be loaded in CSQL with mode 1.
#    and table t2 should be loaded with mode 2 in csqltable .conf file.

#    select * from t1, should show all the records,
#    select * from t2 should show the records as per the condition in the time o     f caching.  	

#Run the test only under csql/test or on this directory.
#otherwise it may fail.

#  Author : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1,t2 in target DB.
isql $DSN < ${REL_PATH}/create.sql >/dev/null 2>&1
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
    isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db

    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -c "t2f1<5" 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
    isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 3;
fi


echo  "select query on t1 and t2 table"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DSN <${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
exit 0;











