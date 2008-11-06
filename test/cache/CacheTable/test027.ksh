#!/bin/sh
#Test case 27.
#	create t1 table with some records in target DB.
#	cache it with -c and -f option
#	again add some more records into t1 in target db.
#	now cache it with -r option
#	it will reload the table t1 in csql with latest records.

#Run this test only under csql/test or on this directory.
#otherwise, it may fail.
#  AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
 then
 REL_PATH=${PWD}/cache/CacheTable
fi

isql myodbc3 < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
 exit 1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1=1" -f "f1,f3,f5" >/dev/null 2>&1
if [ $? -ne 0 ]
 then
 rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
 touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
 $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
 isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
 exit 2;
fi

isql myodbc3 < ${REL_PATH}/frecords.sql >/dev/null 2>&1

 # again reload table  with -r option.
 $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r >/dev/null 2>&1
 if [ $? -ne 0 ]
 then
   rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
   touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 3;
fi

#after reload, select from t1
echo "after reload , select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
 then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 5;
fi
 
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;
