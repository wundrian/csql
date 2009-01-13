#!/bin/sh

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

echo "create table t1 (f1 int,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql

for((a=1;a<=5;a++))
do
echo "insert into t1 values($a,'INDIA$a');"
echo "insert into t1 values($a+10 , NULL);"
done>>${REL_PATH}/t1create.sql
echo "t1create.sql file created"
echo "select * from t1;">${REL_PATH}/sel.sql
echo "select file created" 
isql $DSN < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
rm /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE

rm -f /tmp/csql/csqltable.conf /tmp/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
echo "drop table t1;">${REL_PATH}/dp.sql
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

echo "Select * from t1 in CSQL"
$CSQL_INSTALL_ROOT/bin/csql -g -s ${REL_PATH}/sel.sql 
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1
   exit 3;
fi

echo "Checking for table created or not"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1
   exit 4;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < ${REL_PATH}/dp.sql >/dev/null 2>&1

rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/sel.sql
rm -f ${REL_PATH}/t1create.sql
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;
