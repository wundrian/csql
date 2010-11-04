#!/bin/ksh
# Test Case
#23.  create table 't1' with 5 fields in Target DB with records.
#	Load the table 't1' in field mode in csql without condition.
#	Example  : select f1,f2,f3 from t1 ; 
#     Select * on CSQL should display values for f1,f2 and f3

#Author : Jitendra Lenka
input=${PWD}/cache/CacheTable/csql.conf
REL_PATH=.
if [ -s "$input" ]
then
      REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
    exit 1;
fi

isql $DS < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    exit 1;
fi

echo Table t1 created with 5 records in target DB.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# cache from target to csql with -f option.
echo "cachetable -t t1 -f \"f1,f2,f3\" "
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -f "f1,f2,f3" 
if [ $? -ne 0 ]
then 
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf
   kill -9 $pid
   isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 2;
fi

echo "select * from t1;"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
 
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
kill -9 $pid
ipcrm -M 4000 -M 4500
 
exit 0;
