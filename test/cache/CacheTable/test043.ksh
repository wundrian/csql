#!/bin/ksh
#   Create t1,t2,t3,t4 and t5 table in target Database
#   Cache all tables specifying different caching modes
#   Use -S option to display cache information about each table
#   drop all tables and use -S option
#   It should display "no cached tables"

input=${PWD}/cache/CacheTable/createtable.sql
REL_PATH=.
if [ -s "$input" ]
then
 REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
 
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DS < ${REL_PATH}/createtable.sql  > /dev/null 2>&1

if [ $? -ne 0 ]
 then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi
 
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

#simple caching
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  exit 3;
fi

#cachetable with condition,"-c" option
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t2 -c "t2f1=11"  > /dev/null 2>&1

if [ $? -ne 0 ]
then 
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  exit 4;
fi

#cache table with "-f" option
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t3 -f "t3f1"  > /dev/null 2>&1
 
if [ $? -ne 0 ]
then
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 5;
fi

# cache table with "-d" option
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t4 -D  > /dev/null  2>&1
    
if [ $? -ne 0 ]
then
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  exit 6;
fi

#cache table with condition, field list and direct option
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t5 -c "t5f1=11" -f "t5f2" -D  > /dev/null  2>&1
     
if [ $? -ne 0 ]
then
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  exit 7;
fi

#describe the cache tables -S option
echo ""
echo "(1). cachetable -S"
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -S  
if [ $? -ne 0 ]
then
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  exit 8;
fi

#Describe the specific cache table with -S option
echo "(2). cachetable -t t5 -S"
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t5 -S
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/droptable.sql > /dev/null 2>&1
  isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1
  cp /tmp/csql.conf $CSQL_CONFIG_FILE
  exit 9;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/droptable.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/droptable.sql >/dev/null 2>&1

#use -S option when there is no table present in cache
echo "(3). cachetable -S (Cross Verification)"
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -S
if [ $? -ne 0 ]
then
 cp /tmp/csql.conf $CSQL_CONFIG_FILE
 exit 10;
fi

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

