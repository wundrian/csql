#!/bin/sh
#Test case 26.
#	create table t1 and t2in target DB with 10 records.
#	Recover the two tables from target db with -R option.
#	The contains in the csqltable.conf file will be like this :
			
#					1:t1 NULL NULL
#					2:t2 t2f1<15 t2f1,t2f3,t2f5

#Run this test only under csql/test or on this directory
#otherwise it may fail.

#AUTHOR : Jitendra Lenka
input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
 then
 REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1,t2 in target DB.
cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/fmodecreate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 exit 1;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "1:t1 NULL NULL NULL"  >/tmp/csql/csqltable.conf
echo "2:t2 NULL t2f1<15 t2f1,t2f3,t2f5" >>/tmp/csql/csqltable.conf

# caching with -R option
$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
  then exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
 then
  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
  isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
  rm -f /tmp/csql/csqltable.conf  /tmp/csql/csql.db
  touch  /tmp/csql/csqltable.conf /tmp/csql/csql.db
  exit 3;
fi

rm -f /tmp/csql/csqltable.conf  /tmp/csql/csql.db
touch  /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
  
exit 0;
 



