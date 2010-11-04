#!/bin/ksh

#  4. Create table t1(f1 int, f2 int, primary key (f1)); in mysql
#     insert into t1 values(1, 11);
#     Cache the table in CSQL.
#     Insert the same tuple in csql.
#     It should fail with unique key violation.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/createt1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
   REL_PATH=${PWD}/cache/Recovery
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


if [ $DSN = "oracle" ]
 then
  isql $DS < $REL_PATH/createt1.oracle > /dev/null 2>&1
  if [ $? -ne 0 ]
   then
     rm -f /tmp/csql/csqlds.conf
     touch /tmp/csql/csqlds.conf
     exit 2;
   fi
 else
  isql $DS < $REL_PATH/createt1.sql > /dev/null 2>&1
  if [ $? -ne 0 ]
   then
     rm -f /tmp/csql/csqlds.conf
     touch /tmp/csql/csqlds.conf
     exit 2;
   fi
fi

if [ $? -ne 0 ]
then
    exit 1;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf 
touch /tmp/csql/csqltable.conf 
echo "1 t1 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert.sql >/dev/null 2>&1 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
    exit 5;
fi

kill -9 $pid > /dev/null 2>&1

isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
ipcrm -M 1199 -M 2277
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
exit 0;

