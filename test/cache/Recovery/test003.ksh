#!/bin/ksh
#  Start TDB and create table in TDB t1(f1 int primary key, f2 int ), 
#     create index idx2 on t1 (f2) and insert 10 records each.
#  Add entry for t1 table in csqltable.conf file. 
#  Recover with csqlserver -c option. 
#  Verify that it recovers the table with both the index information and 
#     all the records using the csqldump tool. 

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
     exit 2;
   fi
 else
  isql $DS < $REL_PATH/createt1.sql > /dev/null 2>&1
  if [ $? -ne 0 ]
   then
     exit 2;
   fi
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "1 t1 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5

rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
   isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
   exit 5;
fi

kill -9 $pid > /dev/null 2>&1

isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
ipcrm -M 1199 -M 2277
rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
exit 0;

