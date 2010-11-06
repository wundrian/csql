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
    echo "CREATE TABLE t1(f1 INT,f2 CHAR(20));" > create.sql
elif [ $DSN = "oracle" ]
then
    echo "CREATE TABLE t1(f1 INT,f2 CHAR(20));" > create.sql
elif [ $DSN = "db2" ]
then
    echo "CREATE TABLE t1(f1 INT,f2 CHAR(20))" > create.sql
else
    echo "CREATE TABLE t1(f1 INT,f2 CHAR(20));" > create.sql
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

if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/selecttest3 2> $0.valgr
else
    ${REL_PATH}/selecttest3
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
