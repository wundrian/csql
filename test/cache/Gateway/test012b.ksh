#!/bin/ksh

#  12.csqlserver not running
#  b)connect, update
#  noncached table in mysql(should work), cached table (work), csql table (fail)

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
rm /tmp/csql.conf

cp $REL_PATH/csql.conf /tmp/csql.conf
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
   isql $DS < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1
fi

if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi
 
if [ $DSN = "oracle" ]
then
   isql $DS < $REL_PATH/orainputt2.oracle > /dev/null 2>&1
elif [ $DSN = "sybase" ]
then
   isql $DS < $REL_PATH/sybaseinputtest12.sql > /dev/null 2>&1
elif [ $DSN = "db2" ]
then
   isql $DS < $REL_PATH/db2inputtest12.sql > /dev/null 2>&1
else
   isql $DS < $REL_PATH/mysqlinputtest12.sql > /dev/null 2>&1
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
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/orainputt3.oracle >/dev/null 2>&1
else
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest12.sql >/dev/null 2>&1
fi

kill -9 $pid 
ipcrm -M 1199 -M 2277

if [ $DSN = "oracle" ]
then
  echo "update t2 set f2='LLL' where f1=20;" >> $REL_PATH/oraupdatet2.sql
  echo "update t1 set f2='LLL' where f1=20;" >> $REL_PATH/oraupdatet1.sql
  echo "update t3 set f2='LLL' where f1=20;" >> $REL_PATH/oraupdatet3.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oraupdatet2.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oraupdatet1.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oraupdatet3.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart2.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart3.sql
else  
  if [ $DSN = "db2" ]
  then
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/db2updatet2.sql
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/db2update.sql
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/db2updatet3.sql
  else
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/updatet2.sql
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/update.sql
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/updatet3.sql
  fi 
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart2.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstart3.sql
fi

isql $DS < $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1

rm -f /tmp/csql/csqltable.conf
rm -f $REL_PATH/oraup*.sql
touch /tmp/csql/csqltable.conf
exit 0;
