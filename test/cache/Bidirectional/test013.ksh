#!/bin/sh
# Test Case
# Create 100 table in target database with a integer primary key.
# Run trigger for all table. Make sure Log table is in target database
# Run cache server with bi-directional and cache flag true. Cache all tables.
# Insert record in each table in target database. Check in csql node records are inserted or not 
# Author := Bijaya

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi

for((a=1; a<=100; a++))
do
echo "create table t$a(f1 int,f2 int,primary key(f1));"
echo "insert into t$a values(1,2);"
done >> $REL_PATH/create100table.sql
echo "table creation file created"

for((a=1; a<=100; a++))
do
echo "insert into t$a values(10,20);"
echo "insert into t$a values(11,21);"
echo "commit;"
done >> $REL_PATH/insertinto100.sql
echo "insert record file creates"

for((a=1; a<=100; a++))
do
echo "echo select * from t$a;"
echo "select * from t$a;"
done >>$REL_PATH/selectfrom100.sql
echo "select file created"

for((a=1; a<=100; a++))
do
echo "drop table t$a;"
done >>$REL_PATH/drop100table.sql

echo "use test;">>$REL_PATH/inserttrigger100.sql
for((a=1; a<=100; a++))
do
echo "drop trigger if exists triggerinsertt$a;"
echo "create trigger triggerinsertt$a AFTER INSERT on t$a FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t$a', NEW.f1, 1,1); End;"
done >> $REL_PATH/inserttrigger100.sql
echo "trigger file generated"

for((a=1; a<=100; a++))
do
echo "drop trigger if exists triggerinsertt$a;"
done >>$REL_PATH/dropinserttrigger.sql
echo "drop trigger file generated"

rm -f /tmp/csql1.conf
cp $REL_PATH/csql1.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql1.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

isql $DSN < $REL_PATH/mysqlcreatelogtable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    rm -f $REL_PATH/create100table.sql
    rm -f $REL_PATH/insertinto100.sql
    rm -f $REL_PATH/selectfrom100.sql
    rm -f $REL_PATH/drop100table.sql
    rm -f $REL_PATH/inserttrigger100.sql
    rm -f $REL_PATH/dropinserttrigger.sql
    exit 1
fi
echo Log table created in target DB
isql $DSN < $REL_PATH/create100table.sql >/dev/null
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN <$REL_PATH/inserttrigger100.sql >/dev/null

for (( a=1; a<=100; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 30
echo "server  started"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    isql $DSN < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
    rm -f $REL_PATH/create100table.sql
    rm -f $REL_PATH/insertinto100.sql
    rm -f $REL_PATH/selectfrom100.sql
    rm -f $REL_PATH/drop100table.sql
    rm -f $REL_PATH/inserttrigger100.sql
    rm -f $REL_PATH/dropinserttrigger.sql
    exit 2
fi

echo "Insert some record in target database"
isql $DSN < ${REL_PATH}/insertinto100.sql >/dev/null 2>&1
sleep 30

echo "Records in csql after insert in target DB"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop100table.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < $REL_PATH/dropinserttrigger.sql >/dev/null 2>&1
isql $DSN < $REL_PATH/mysqldeletelogtable.sql >/dev/null 2>&1
kill -2 $pid
ipcrm -M 4000 -M 4500

rm -f $REL_PATH/create100table.sql
rm -f $REL_PATH/insertinto100.sql
rm -f $REL_PATH/selectfrom100.sql
rm -f $REL_PATH/drop100table.sql
rm -f $REL_PATH/inserttrigger100.sql
rm -f $REL_PATH/dropinserttrigger.sql
exit 0;
