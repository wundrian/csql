#!/bin/ksh

#  4.insert, select, update, delete on table which is not there in both mysql and csql. All should fail.

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

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

if [ $DSN = "oracle" ]
then
    for a in 51 52 53 54 55
    do
       echo "insert into t1 values($a,'KKK');"
    done >> $REL_PATH/oracsqlinputt1.sql
    $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oracsqlinputt1.sql >/dev/null 2>&1
else
    if [ $DSN = "db2" ]
    then
        $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqldb2inputtest1.sql >/dev/null 2>&1
    else
        $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql >/dev/null 2>&1
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 
isql $DS < $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

if [ $DSN = "oracle" ]
then
   echo "select * from t1 where f1 in(10,30,50,54);" >> $REL_PATH/oraselect.sql
   echo "select * from t1 where f1 between 20 and 54;" >> $REL_PATH/oraselect.sql
   echo "update t1 set f2='LLL' where f1=20;" >> $REL_PATH/oraupdate.sql
   echo "delete from t1 where f2='BBB';" >> $REL_PATH/oradelete.sql
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oraselect.sql >/dev/null 2>&1
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oraupdate.sql >/dev/null 2>&1
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oradelete.sql >/dev/null 2>&1
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql >/dev/null 2>&1
else
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/select.sql 2>/dev/null
   if [  $DSN = "db2" ]
   then
       $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/db2update.sql 2>/dev/null
   else
       $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/update.sql 2>/dev/null
   fi
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/delete.sql 2>/dev/null
   $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql 2>/dev/null
fi

isql $DS < $REL_PATH/selectstar.sql 2>/dev/null
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

isql $DS < $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
kill -9 $pid 
rm -f $REL_PATH/ora*.sql
ipcrm -M 1199 -M 2277
exit 0;
