#!/bin/ksh

#  Create 't1' table with f1 int, f2 char(10) ,primarykey(f1)
#  Insert some records with null values
#  Cache t1 from target to csql. 
#  Select from CSQL cache node .It should give actual data as in target database
#  it should be unloaded by -u option

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

if [ "$DSN" = "sybase" ]
then
    echo "create table t1 (f1 int,f2 char(10) NULL,primary key(f1));" >${REL_PATH}/t1create.sql
elif [ "$DSN" = "db2" ]
then
    echo "create table t1 (f1 int NOT NULL,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql
else
    echo "create table t1 (f1 int,f2 char(10) ,primary key(f1));" >${REL_PATH}/t1create.sql
fi


for a in 1 2 3 4 5 
do
echo "insert into t1 values($a,'INDIA$a');"
echo "insert into t1 values($a+10 , NULL);"
done>>${REL_PATH}/t1create.sql
echo "t1create.sql file created"
echo "select * from t1;">${REL_PATH}/sel.sql
echo "select file created" 
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 2;
fi
echo "Select * from t1 in CSQL"
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sel.sql 
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 3;
fi

echo "Checking for table created or not"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/sel.sql
   rm -f ${REL_PATH}/t1create.sql
   exit 5;
fi
echo "cache table 't1' unloaded by -u option"
echo "drop table t1;">${REL_PATH}/dp.sql
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/sel.sql
rm -f ${REL_PATH}/t1create.sql
exit 0;
