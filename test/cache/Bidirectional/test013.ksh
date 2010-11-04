#!/bin/ksh
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
a=1
while [[ $a -lt 101 ]];do
    if [ $DSN = "oracle" ]
    then
        echo "create table t$a(f1 number(8),f2 number(8),primary key(f1));"
    else
        echo "create table t$a(f1 int,f2 int,primary key(f1));"
    fi
    echo "insert into t$a values(1,2);"
    (( a +=1 ))
done >> $REL_PATH/create100table.sql
echo "table creation file created"
a=1
while [[ $a -lt 101 ]];do
    echo "insert into t$a values(10,20);"
    echo "insert into t$a values(11,21);"
    echo "commit;"
    (( a +=1 ))
done >> $REL_PATH/insertinto100.sql
echo "insert record file creates"
a=1
while [[ $a -lt 101 ]];do
    echo "echo select * from t$a;"
    echo "select * from t$a;"
    (( a +=1 ))
done >>$REL_PATH/selectfrom100.sql

echo "select file created"
a=1
while [[ $a -lt 101 ]];do
    echo "drop table t$a;"
    (( a +=1 ))
done >>$REL_PATH/drop100table.sql

rm -f /tmp/csql1.conf
cp $REL_PATH/csql1.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql1.conf
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql1/csqlds.conf
touch /tmp/csql1/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
echo DSN=$DSN >>$CSQL_CONFIG_FILE
if [ $DSN = "myodbc3" ]
then
    echo "use test;">>$REL_PATH/inserttrigger100.sql
    a=1
    while [[ $a -lt 101 ]];do
       echo "drop trigger if exists triggerinsertt$a;"
       echo "create trigger triggerinsertt$a AFTER INSERT on t$a FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t$a', NEW.f1, 1,1); End;"
       (( a +=1 ))
    done >> $REL_PATH/inserttrigger100.sql
    echo "trigger file generated"
    a=1
    while [[ $a -lt 101 ]];do
       echo "drop trigger if exists triggerinsertt$a;"
       (( a +=1 ))
    done >>$REL_PATH/dropinserttrigger.sql
    echo "drop trigger file generated"
    LOG_FILE=$REL_PATH/mysqlcreatelogtable.sql
elif [ "$DSN" = "psql" ]
then
    echo "CREATE LANGUAGE plpgsql;">$REL_PATH/inserttrigger100.sql
    a=1
    while [[ $a -lt 101 ]];do
       echo "DROP FUNCTION IF EXISTS log_insert_t$a() CASCADE ;"
       echo "CREATE OR REPLACE FUNCTION log_insert_t$a() RETURNS trigger AS \$triggerinsertt$a$ BEGIN insert into csql_log_int (tablename, pkid, operation, cacheid) values ('t$a', NEW.f1, 1, 1); RETURN NEW; END; \$triggerinsertt$a$ LANGUAGE plpgsql;"
       echo "create trigger triggerinsertt$a AFTER INSERT on t$a FOR EACH ROW EXECUTE PROCEDURE log_insert_t$a();"
       (( a +=1 ))
    done >> $REL_PATH/inserttrigger100.sql
    echo "trigger file generated"
    a=1
    while [[ $a -lt 101 ]];do
        echo "DROP FUNCTION IF EXISTS log_insert_t$a() CASCADE ;"
        (( a +=1 ))
    done >$REL_PATH/dropinserttrigger.sql
    echo "drop trigger file generated"
    LOG_FILE=$REL_PATH/psqlcreatelogtable.sql
elif [ "$DSN" = "oracle" ]
then
   a=1
   while [[ $a -lt 101 ]];do
       echo "CREATE OR REPLACE TRIGGER triggert$a AFTER insert on t$a FOR EACH ROW declare  rid PLS_INTEGER; begin  SELECT CSQL_ID.NEXTVAL INTO rid  FROM dual;  if inserting then insert into csql_log_int values ('t$a',:new.f1,1,1,rid);  end if; end;"
       (( a +=1 ))
   done >> $REL_PATH/inserttrigger100.sql
   echo "trigger file generated"
   a=1
   while [[ $a -lt 101 ]];do
       echo "drop trigger triggert$a;"
       (( a +=1 ))
   done >$REL_PATH/dropinserttrigger.sql
   echo "drop trigger file generated"
   LOG_FILE=$REL_PATH/oraclecreatelogtable.sql
elif [ "$DSN" = "sybase" ]
then
   echo "sybase Trigger Missing"
fi
#echo $DS
isql $DS < $LOG_FILE >/dev/null 2>&1
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
isql $DS < $REL_PATH/create100table.sql >/dev/null
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS <$REL_PATH/inserttrigger100.sql >/dev/null

a=1
while [[ $a -lt 101 ]];do
    echo "1 t$a NULL NULL NULL $DSN"
    (( a +=1 ))
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 30
echo "server  started"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    isql $DS < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
    rm -f $REL_PATH/create100table.sql
    rm -f $REL_PATH/insertinto100.sql
    rm -f $REL_PATH/selectfrom100.sql
    rm -f $REL_PATH/drop100table.sql
    rm -f $REL_PATH/inserttrigger100.sql
    rm -f $REL_PATH/dropinserttrigger.sql
    exit 2
fi

echo "Insert some record in target database"
isql $DS < ${REL_PATH}/insertinto100.sql >/dev/null 2>&1
sleep 30

echo "Records in csql after insert in target DB"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop100table.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $REL_PATH/dropinserttrigger.sql >/dev/null 2>&1
isql $DS < $REL_PATH/mysqldeletelogtable.sql >/dev/null 2>&1
kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
kill -9 $pid
ipcrm -M 4000 -M 4500

rm -f $REL_PATH/create100table.sql
rm -f $REL_PATH/insertinto100.sql
rm -f $REL_PATH/selectfrom100.sql
rm -f $REL_PATH/drop100table.sql
rm -f $REL_PATH/inserttrigger100.sql
rm -f $REL_PATH/dropinserttrigger.sql
exit 0;
