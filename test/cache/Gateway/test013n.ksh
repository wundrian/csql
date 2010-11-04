#!/bin/ksh

#  Create 't1' table with f1 int, f2 char(10) ,primarykey(f1) in target database
#  Insert some records with null values
#  Select from CSQL with -g .It should give actual data as in target database
#  it should be unloaded by -u option

input=${PWD}/cache/Gateway/complex.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi

cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
echo PORT=6026 >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
echo DSN=$DSN >>$CSQL_CONFIG_FILE
if [ $DSN = "sybase" ]
then
    echo "create table t1 (f1 int ,f2 char(10) NULL,primary key(f1));" >${REL_PATH}/t1create.sql
elif [ $DSN = "db2" ]
then
    echo "create table t1 (f1 int NOT NULL ,f2 char(10) ,primary key(f1));" >${REL_PATH}/t1create.sql
else
    echo "create table t1 (f1 int,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql
fi

for a in 1 2 3 4 5
do
echo "insert into t1 values($a,'INDIA$a');"
echo "insert into t1 values($a+10 , NULL);"
done>>${REL_PATH}/t1create.sql
echo "t1create.sql file created"
echo "select * from t1;">${REL_PATH}/sel.sql
echo "select file created" 
isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "drop table t1;">${REL_PATH}/dp.sql

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

echo "Select * from t1 in CSQL"
$CSQL_INSTALL_ROOT/bin/csql -H localhost -P 6026 -g -s ${REL_PATH}/sel.sql 
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
   exit 3;
fi

echo "Checking for table created or not"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
   exit 4;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1

rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/sel.sql
rm -f ${REL_PATH}/t1create.sql
kill -9 $pid
ipcrm -M 1199 -M 2277
kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
exit 0;
