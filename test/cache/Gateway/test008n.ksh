#!/bin/ksh

#  8.Cached table there in csql, but join with another cached table in csql. It should get the correct value from mysql.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm -f /tmp/csql.conf

cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
echo PORT=6014 >>/tmp/csql.conf
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
   isql $DS < $REL_PATH/orainputt1.oracle > /dev/null 2>&1
elif [ $DSN = "sybase" ]
then
   isql $DS < $REL_PATH/sybaseinputtest5.sql > /dev/null 2>&1
elif [ $DSN = "db2" ]
then
   isql $DS < $REL_PATH/db2inputtest5.sql > /dev/null 2>&1
else
   isql $DS < $REL_PATH/mysqlinputtest5.sql > /dev/null 2>&1
fi

if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi

if [ $DSN = "oracle" ]
then
  isql $DS < $REL_PATH/orainputt2.oracle > /dev/null 2>&1
else
  isql $DS < $REL_PATH/mysqlinputtest8.sql > /dev/null 2>&1
fi
# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

for a in 1 2 
do
   $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $DSN
   if [ $? -ne 0 ]
   then
      kill -9 $pid
      ipcrm -M 1199 -M 2277
      exit 3;
   fi
done >> /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6014 -g -s $REL_PATH/join.sql

isql $DS < $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277
kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
exit 0;
