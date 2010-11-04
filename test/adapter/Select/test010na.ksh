#!/bin/ksh
#create table T1 with 10 fields,( F2 NOT NULL , F3 CHAR(20) DEFAULT 'LAKSHYA')
#insert 10 rows for 9 Fields except F3 Field into the table
#noofprojFields should return 5.
#getProjFldInfo() for all fields.
#select with 5 parameters withIwhere clause.(WHERE F1=100)
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
${REL_PATH}/selecttest10na
if [ $? -ne 0 ]
then
   kill -9 $pid
   kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
   exit 1;
fi
rm -f /tmp/csql.conf
kill -9 $pid 
exit 0;
