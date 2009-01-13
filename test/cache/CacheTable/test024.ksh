#!/bin/sh
#Test Case 24
#	create table t1 and t2 in target db with 10 records
#	load t1 table in csql with condition option and without field mode option.
#	load table t2 with condition and field mode option.
#	select from both the table

#Run the test only under csql/test or on this directory.
#otherwise it may fail.

#Author : Jitendra Lenka

input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
then
   REL_PATH=${PWD}/cache/CacheTable
fi
isql $DSN < ${REL_PATH}/fmodecreate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi
echo Table t1 and t2 created in target DB.
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "cachetable -t t1 -c \"t1f1<5\" "
echo "cachetable -t t2 -c \"t2f1>15\" -f \"t2f1,t2f3,t2f5\" "

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "t1f1<5" >/dev/null 2>&1
 if [ $? -ne 0 ]
 then
   isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
   touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
   exit 2;
 fi

 $CSQL_INSTALL_ROOT/bin/cachetable -t t2 -c "t2f1>15" -f "t2f1,t2f3,t2f5"
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


