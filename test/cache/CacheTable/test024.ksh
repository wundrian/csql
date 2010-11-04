#!/bin/ksh
#Test Case 24
#  create table t1 and t2 in target db with 10 records
#  load t1 table in csql with condition option and without field mode option.
#  load table t2 with condition and field mode option.
#  select from t2 table in CSQL and verify it displays only specified field
#  values which satisfies the condition.

#Author : Jitendra Lenka

input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
then
   REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
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

echo "cachetable -t t1 -c \"t1f1<5\" "
echo "cachetable -t t2 -c \"t2f1>15\" -f \"t2f1,t2f3,t2f5\" "

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "t1f1<5" >/dev/null 2>&1
 if [ $? -ne 0 ]
 then
   isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf
   exit 2;
 fi

 $CSQL_INSTALL_ROOT/bin/cachetable -t t2 -c "t2f1>15" -f "t2f1,t2f3,t2f5"
  if [ $? -ne 0 ]
  then
     rm -f /tmp/csql/csqltable.conf
     touch /tmp/csql/csqltable.conf
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
     isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
     exit 3;
 fi

echo  "select query on t1 and t2 table"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
 
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DS <${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
exit 0;
