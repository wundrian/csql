#!/bin/ksh
#One connection working with multiple statements
#create table T1 with two fields,
#One connection working with multiple statements simultaneously for csql,
#Create conn
#create 3 stmts for inserting into 5 tables and set the same connection
#insert into all 3 tables and commit the transaction
#free all stmts
#select the records from 3 tables in same connection
#free all stmt;
#Author : Nihar Paital
#

CSQL_CONF=${PWD}/adapter/Select/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/adapter/Select
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
#echo PORT= >>/tmp/csql.conf
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

$CSQL_INSTALL_ROOT/bin/csqlsqlserver  >/dev/null 2>&1 &
pid=$!
sleep 5
${REL_PATH}/singleconnadapterna
if [ $? -ne 0 ]
then
   kill -9 $pid
   kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
   exit 1;
fi
rm -f /tmp/csql.conf
kill -9 $pid 
exit 0;
