#!/bin/ksh
#Test case 26.
#   create table t1 and t2in target DB with 10 records.
#   Recover the two tables from target db with -R option.
#   The contains in the csqltable.conf file will be like this :
#			1:t1 NULL NULL
#			2:t2 t2f1<15 t2f1,t2f3,t2f5

#AUTHOR : Jitendra Lenka
input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
 then
 REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

# create table t1,t2 in target DB.
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < ${REL_PATH}/fmodecreate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 exit 1;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "1 t1 NULL NULL NULL $DSN"  >/tmp/csql/csqltable.conf
echo "2 t2 NULL t2f1<15 t2f1,t2f3,t2f5 $DSN" >>/tmp/csql/csqltable.conf

# caching with -R option
$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
  then exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
 then
  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
  isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
  rm -f /tmp/csql/csqltable.conf   
  touch  /tmp/csql/csqltable.conf
  exit 3;
fi

rm -f /tmp/csql/csqltable.conf   
touch  /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
  
exit 0;
