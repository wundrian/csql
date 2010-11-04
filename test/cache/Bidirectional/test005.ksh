#!/bin/ksh
# Test Case

#Bi-directional mutiple cache node test
#Two Cache Node and t1 and t2 table to be cached
# insert operation in target database

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
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
if [ "$DSN" = "myodbc3" ]
then
   LOG_FILE=$REL_PATH/mysqlcreatelogtable.sql
   TRI_FILE1=$REL_PATH/trigger.sql
   TRI_FILE2=$REL_PATH/trigger1.sql
elif [ "$DSN" = "psql" ]
then
    LOG_FILE=$REL_PATH/psqlcreatelogtable.sql
    TRI_FILE1=$REL_PATH/trigger.psql
    TRI_FILE2=$REL_PATH/trigger1.psql
elif [ "$DSN" = "oracle" ]
then
    LOG_FILE=$REL_PATH/oraclecreatelogtable.sql
    TRI_FILE1=$REL_PATH/triggermul.oracle
    TRI_FILE2=$REL_PATH/trigger1mul.oracle
elif [ "$DSN" = "sybase" ]
then
    LOG_FILE=$REL_PATH/sybasecreatelogtable.sql
    TRI_FILE1=$REL_PATH/trigger.sybase
    TRI_FILE2=$REL_PATH/trigger1.sybase
elif [ "$DSN" = "db2" ]
then
    LOG_FILE=$REL_PATH/db2createlogtable.sql
    TRI_FILE1=$REL_PATH/trigger.db2
    TRI_FILE2=$REL_PATH/trigger1.db2
else
    LOG_FILE=
    TRI_FILE1=
    TRI_FILE2=
fi

#echo $DS

isql $DS < $LOG_FILE >/dev/null 2>&1 
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi

echo table csql_log_int is created with records in target db

isql $DS < $REL_PATH/create.sql >/dev/null 2>&1 
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $TRI_FILE1 >/dev/null
isql $DS < $TRI_FILE2 >/dev/null


$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "server 1 started"

for  a in 1 2
do
   $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $DSN
   if [ $? -ne 0 ]
   then
       isql $DS < ${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
       isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
       kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
       kill -9 $pid
       ipcrm -M 4000 -M 4500
       exit 3;
   fi
   sleep 2
done

echo "cache node 2"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql 
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    isql $DS < ${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 2
fi
mkdir /tmp/log/csql1 >/dev/null 2>&1
mkdir /tmp/csql1 >/dev/null 2>&1 
rm -f /tmp/csql1/csqltable.conf
touch /tmp/csql1/csqltable.conf

rm -f /tmp/csql1.conf
cp $REL_PATH/conf/csql.conf /tmp/csql1.conf
export CSQL_CONFIG_FILE=/tmp/csql1.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid1=$!
sleep 5
echo "server 2 started"

for a in 1 2
do
   $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $DSN
   if [ $? -ne 0 ]
   then
       isql $DS < ${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
       isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
       kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
       kill -9 $pid $pid1
       ipcrm -M 4000 -M 4500 -M 5000 -M 5500
       exit 6;
   fi
   sleep 2
done 


echo "cache node 1"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    isql $DS < ${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid $pid1
    ipcrm -M 4000 -M 4500 -M 5000 -M 5500
    exit 4
fi

isql $DS < ${REL_PATH}/insert.sql >/dev/null 2>&1
sleep 20 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

export CSQL_CONFIG_FILE=/tmp/csql.conf
echo "cache node 2"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
rm -f /tmp/csql1/csqltable.conf
touch /tmp/csql1/csqltable.conf
isql $DS < ${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
kill -9 $pid $pid1
ipcrm -M 4000 -M 4500 -M 5000 -M 5500
exit 0;
