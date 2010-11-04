#!/bin/ksh

#  4.After connect, csql goes down, then all insert operations should go to MySQL directly for cached tables and MySQL tables.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/FailOver/csql.conf
input=${PWD}/cache/FailOver/csqlinputt3.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/FailOver
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

isql $DS < $REL_PATH/dropt1t2.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 2;
fi

if [ $DSN = "oracle" ]
then
   isql $DS < $REL_PATH/orainputt1.oracle >/dev/null 2>&1
elif [ $DSN = "sybase" ] 
then
   isql $DS < $REL_PATH/sybaseinputtest1.sql >/dev/null 2>&1 
elif [ $DSN = "db2" ] 
then
   isql $DS < $REL_PATH/db2inputtest1.sql >/dev/null 2>&1 
else
   isql $DS < $REL_PATH/mysqlinputtest1.sql >/dev/null 2>&1
fi

if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

echo "table t1(to be cached) inserted into target db"
# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -d $DSN
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   exit 3;
fi

echo "table t1 cached into csql"

if [ $DSN = "oracle" ]
then
   isql $DS < $REL_PATH/orainputt2.oracle >/dev/null 2>&1
elif [ $DSN = "sybase" ] 
then
   isql $DS < $REL_PATH/sybaseinputtest2.sql >/dev/null 2>&1 
elif [ $DSN = "db2" ] 
then
   isql $DS < $REL_PATH/db2inputtest2.sql >/dev/null 2>&1 
else
   isql $DS < $REL_PATH/mysqlinputtest2.sql >/dev/null 2>&1
fi

echo "table t2(not cached) inserted into target db"

if [ $DSN = "oracle" ]
then
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/orainputt3.oracle >/dev/null 2>&    1
else
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputt3.sql >/dev/null 2>&1
fi
echo "table t3 inserted into csql db"

$REL_PATH/deleteconncsqldown &
bgproc=$!
kill -9 $pid 
ipcrm -M 1199 -M 2277
echo "csql server is down"
wait $bgproc
isql $DS < $REL_PATH/dropt1t2.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 4;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
exit 0;
