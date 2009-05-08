#!/bin/sh
# Table recovery with more than one Composite index
# a.start mysqlserver and create table in mysql t1(f1 int , f2 int,f3 int,f4 char(10),primary key(f1,f2) ), create index idx2 on t1 (f2,f4),create index idx3 on t1(f3,f1)
# b.edit csqltable.conf file and add entry for t1 table.
# c.csqlserver -c
# verify that it recovers the table with both the index information and all the records using the csqldump tool. 
#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/createt1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi
echo "create table t1(f1 int , f2 int,f3 int,f4 char(10),primary key(f1,f2));">$REL_PATH/t1.sql
echo "create index ix2 on t1(f3,f4);">>$REL_PATH/t1.sql

rm /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE
echo CACHE_TABLE=true >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/t1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    mv /tmp/csql.conf $CSQL_CONFIG_FILE
    rm -f $REL_PATH/t1.sql
    exit 1;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<2; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c > /dev/null 2>&1 & 
pid=$!
sleep 5

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
echo "drop table t1;">>$REL_PATH/drt1.sql

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
    mv /tmp/csql.conf $CSQL_CONFIG_FILE
    rm -f $REL_PATH/t1.sql
    isql $DSN < $REL_PATH/drt1.sql > /dev/null 2>&1
    rm -f $REL_PATH/drt1.sql
    exit 2;
fi

kill $pid > /dev/null 2>&1
isql $DSN < $REL_PATH/drt1.sql > /dev/null 2>&1
rm -f $REL_PATH/t1.sql
rm -f $REL_PATH/drt1.sql
ipcrm -M 1199
ipcrm -M 2277
mv /tmp/csql.conf $CSQL_CONFIG_FILE
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;

