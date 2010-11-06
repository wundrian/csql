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
    
echo "CREATE TABLE T1(f1 INT,f2 CHAR(34));" > create.sql
echo "CREATE TABLE T2(f1 INT,f2 CHAR(34));" >> create.sql
echo "CREATE TABLE T3(f1 INT,f2 CHAR(34));" >> create.sql

isql $DS < create.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

echo "drop table T1;" > drop.sql
echo "drop table T2;" >> drop.sql
echo "drop table T3;" >> drop.sql

echo "SELECT * FROM T1;" >sel.sql
echo "SELECT * FROM T2;" >>sel.sql
echo "SELECT * FROM T3;" >>sel.sql

$CSQL_INSTALL_ROOT/bin/cachetable -t T1
if [ $? -ne 0 ]
then 
    isql $DS < drop.sql >/dev/null 2>&1
    kill -9 $pid
    ipcrm -M 4567 -M 5678 -M 1950 
    rm -f create.sql drop.sql sel.sql
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t T2
if [ $? -ne 0 ]
then 
    isql $DS < drop.sql >/dev/null 2>&1
    kill -9 $pid
    ipcrm -M 4567 -M 5678 -M 1950 
    rm -f create.sql drop.sql sel.sql
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t T3
if [ $? -ne 0 ]
then 
    isql $DS < drop.sql >/dev/null 2>&1
    kill -9 $pid
    ipcrm -M 4567 -M 5678 -M 1950 
    rm -f create.sql drop.sql sel.sql
    exit 4;
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/singleconngateway 2> $0.valgr
else
    ${REL_PATH}/singleconngateway
    if [ $? -ne 0 ]
    then
       isql $DS < drop.sql >/dev/null 2>&1
       $CSQL_INSTALL_ROOT/bin/cachetable -t T1 -u
       $CSQL_INSTALL_ROOT/bin/cachetable -t T2 -u
       $CSQL_INSTALL_ROOT/bin/cachetable -t T3 -u
       $CSQL_INSTALL_ROOT/bin/csql -s drop.sql
       kill -9 $pid
       ipcrm -M 4567 -M 5678 -M 1950 
       rm -f create.sql drop.sql sel.sql
       exit 5;
    fi
fi

isql $DS < sel.sql 
$CSQL_INSTALL_ROOT/bin/csql -s sel.sql

isql $DS < drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/cachetable -t T1 -u
$CSQL_INSTALL_ROOT/bin/cachetable -t T2 -u
$CSQL_INSTALL_ROOT/bin/cachetable -t T3 -u
kill -9 $pid
ipcrm -M 4567 -M 5678 -M 1950 
rm -f /tmp/csql.conf
rm -f create.sql drop.sql sel.sql
exit 0;
