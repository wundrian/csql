#!/bin/ksh

CSQL_CONF=${PWD}/sqlgw/Select/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/sqlgw/Select
fi
rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp/csql.conf

export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf


$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
    
if [ $DSN = "psql" ]
then 
    echo "CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 FLOAT4,f5 FLOAT4,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT);" > create.sql
elif [ $DSN = "sybase" ]
then
    echo "CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30) NULL,f4 REAL,f5 REAL,f6 DATE,f7 TIME,f8 DATETIME,f9 INT,f10 BIGINT);" > create.sql   
elif [ $DSN = "oracle" ]
then
   echo "CREATE TABLE t1(f1 number(9),f2 number(4),f3 CHAR(30),f4 FLOAT,f5 FLOAT,f6 DATE,f8 TIMESTAMP,f9 number(9),f10 number(18));" > create.sql
elif [ $DSN = "db2" ]
then
    echo "CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30), f4 REAL,f5 REAL,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT)" > create.sql   
else
    echo "CREATE TABLE t1(f1 INT,f2 SMALLINT,f3 CHAR(30),f4 FLOAT,f5 FLOAT,f6 DATE,f7 TIME,f8 TIMESTAMP,f9 INT,f10 BIGINT);" > create.sql   
fi

isql $DS < create.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

echo "drop table t1;" > drop.sql

$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then 
    isql $DS < drop.sql >/dev/null 2>&1
    kill -9 $pid
    ipcrm -M 4567 -M 5678 -M 1950 
    rm -f create.sql drop.sql
    exit 1;
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/selecttest8 2> $0.valgr
else
    ${REL_PATH}/selecttest8
    if [ $? -ne 0 ]
    then
       isql $DS < drop.sql >/dev/null 2>&1
       $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
       kill -9 $pid
       ipcrm -M 4567 -M 5678 -M 1950 
       rm -f create.sql drop.sql
       exit 2;
    fi
fi

isql $DS < drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
kill -9 $pid
ipcrm -M 4567 -M 5678 -M 1950 
rm -f /tmp/csql.conf
rm -f create.sql drop.sql
exit 0;
