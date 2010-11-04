#!/bin/ksh
# Test Case

# Bi-directional cache  test
# Create table t1 with field f1 int unique,f2 char,f3 smallint , f4 bigint ,primary key(f2). Make bidirectional flag and cache flag true. run trigger ,create log table in target db.Cache the table. 
# Insert some record chack it should updateed in cache node.
# Author:= Bijaya

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi
rm /tmp/csql.conf
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
    LOG_FILE=
    TRI_FILE1=
    TRI_FILE2=
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
 
echo Log table created in target DB

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "create table t1(f1 int ,f2 char(12),f3 int, f4 int,primary key(f2));">$REL_PATH/t1.sql
echo "create unique index ind on t1(f1) ;">>$REL_PATH/t1.sql
for a in 11 12 13 14 
do
echo "insert into t1 values($a,'papu$a',12,$a+123124);"
done>>$REL_PATH/t1.sql

isql $DS < $REL_PATH/t1.sql  >/dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "unable to creste in target db"
    rm -f $REL_PATH/t1.sql
    exit 2
fi
isql $DS <$TRI_FILE1 >/dev/null

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "server  started"
echo "drop table t1;">${REL_PATH}/dt1.sql
if [ $DSN = "oracle" -o $DSN = "sybase" ]
then
{
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -f f1,f2,f4 -p f1 -F
if [ $? -ne 0 ]
then
    echo "Unable to cache"
    isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
    isql $DS <${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 3
fi
}
else
{
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -f f1,f2,f4 -p f1
if [ $? -ne 0 ]
then
    echo "Unable to cache"
    isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql
    isql $DS <${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 3
fi
}
fi
echo "select * from t1;">$REL_PATH/sel.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/sel.sql
if [ $? -ne 0 ]
then
    echo "In select"
    isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql $REL_PATH/sel.sql
    isql $DS <${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 4
fi

echo "insert into t1 values(17,'papu',12,123124);">$REL_PATH/insert1.sql
echo "insert into t1 values(7,'biju',12,123125);">>$REL_PATH/insert1.sql
echo "insert into t1 values(10,'tapu',12,1231266);">>$REL_PATH/insert1.sql
isql $DS < ${REL_PATH}/insert1.sql >/dev/null 2>&1
sleep 20 
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/sel.sql
if [ $? -ne 0 ]
then
    echo "In 2nd select"
    isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql $REL_PATH/sel.sql $REL_PATH/insert1.sql
    isql $DS <${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1
    kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 5
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
isql $DS <${REL_PATH}/dt1.sql  >/dev/null 2>&1
isql $DS <${REL_PATH}/mysqldeletelogtable.sql >/dev/null 2>&1

rm -f $REL_PATH/t1.sql ${REL_PATH}/dt1.sql $REL_PATH/sel.sql $REL_PATH/insert1.sql
kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0

