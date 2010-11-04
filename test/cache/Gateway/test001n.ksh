#!/bin/ksh

# 1. Create table t1 in MySQL with all supported data types in it. and insert 10 records in it.
# Cache the table in CSQL. and run csqlserver -c to load the records.
# insert 10 more records using csql tool.
# select records with WHERE clause containing parameters for all the fields with different data types.
# update all fields with WHERE clause on primary key
# delete records with WHERE clause on all fields

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input"  ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm -f /tmp/csql.conf

cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
echo PORT=6028 >>/tmp/csql.conf
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
    echo "DSN is not set for target db"
    exit 2; 
fi

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

if [ $DSN = "oracle" ]
then
   for a in 51 52 53 54 55 
   do
     echo "insert into t1 values($a,'KKK');"
   done >> $REL_PATH/oracsqlinputt1.sql
   $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/oracsqlinputt1.sql >/dev/null 2>&1
else
   if [ $DSN = "db2" ]
   then
       $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/csqldb2inputtest1.sql  >/dev/null 2>&1
   else
       $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/csqlinputtest1.sql  >/dev/null 2>&1
   fi
fi

if [ $? -ne 0 ]
then
    echo "Server Not Open"
    exit 4
fi

$CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/selectstar.sql
isql $DS < $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

if [ $DSN = "oracle" ]
then
  echo "select * from t1 where f1 in(10,30,50,54);" >> $REL_PATH/oraselect.sql
  echo "select * from t1 where f1 between 20 and 54;" >> $REL_PATH/oraselect.sql
  echo "update t1 set f2='LLL' where f1=20;" >> $REL_PATH/oraupdate.sql
  echo "delete from t1 where f2='BBB';" >> $REL_PATH/oradelete.sql
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/oraselect.sql 
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/oraupdate.sql >/dev/null 2>&1
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/oradelete.sql >/dev/null 2>&1
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/selectstar.sql
else
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/select.sql
  if [ $DSN = "db2" ]
  then
      $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/db2update.sql >/dev/null 2>&1 
  else
      $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/update.sql >/dev/null 2>&1 
  fi
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/delete.sql >/dev/null 2>&1 
  $CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6028 -g -s $REL_PATH/selectstar.sql
fi


isql $DS < $REL_PATH/selectstar.sql
isql $DS < $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
rm -f $REL_PATH/ora*.sql
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
kill -9 $pid 
ipcrm -M 1199 -M 2277 
kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
exit 0;
