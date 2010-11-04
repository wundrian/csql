#!/bin/ksh
# Test Case

# Bi-directional cache  test
# Cache t1 and t2 table 
# Set bidirectional flag in csql.conf to true,delete log table from target db if exist 

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
    TRI_FILE1=$REL_PATH/trigger.oracle
    TRI_FILE2=$REL_PATH/trigger1.oracle
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
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS < $REL_PATH/create.sql >/dev/null 2>&1 
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    exit 1
fi
echo "drop table csql_log_int;">$REL_PATH/log.sql
echo No log table in target DB
isql $DS <$REL_PATH/log.sql >/dev/null 2>&1 
rm -f $REL_PATH/log.sql
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS <$TRI_FILE1 >/dev/null
isql $DS <$TRI_FILE2  >/dev/null


$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
for  a in 1 2 
do
   $CSQL_INSTALL_ROOT/bin/cachetable -t t$a -d $DSN
   if [ $? -ne 0 ]
   then
       kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
       kill -9 $pid
       isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
       ipcrm -M 4000 -M 4500
       exit 3;
   fi
done 
echo "server  started"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql 
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    ipcrm -M 4000 -M 4500
    exit 2
fi

isql $DS < ${REL_PATH}/insert.sql >/dev/null 2>&1
sleep 15
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0;
