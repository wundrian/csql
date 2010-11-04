#!/bin/ksh
#Test Case
#17. Create table t1 and t2 in target DB with 10 records.
#    Add following entries in csqltable.conf file: 
#      				1:t1 NULL
#				2:t2 t2f1<5
#    Recover the two tables from the target DB with -R option.
#    CSQL should contain 10 records of t1 and 4 records of t2

#Run this test only under csql/test or on this directory
#otherwise it may fail.

#AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

# create table t1,t2 in target DB.
isql $DS < ${REL_PATH}/create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi
echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "1 t1 NULL NULL NULL $DSN"  > /tmp/csql/csqltable.conf 
echo "2 t2 NULL t2f1<5 NULL $DSN" >> /tmp/csql/csqltable.conf     

# caching with -R option
$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
   isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf   
   touch  /tmp/csql/csqltable.conf
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

rm -f /tmp/csql/csqltable.conf   
touch  /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;
