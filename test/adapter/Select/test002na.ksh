#!/bin/ksh
#create table T1 with 10 fields,
#insert 10 rows into the table ,
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
if [ -z "$DBUSER" ]
then
   echo DSN=$DSN >>$CSQL_CONFIG_FILE
   if [ $DSN = "psql" ]
   then
      echo TARGET_DATABASE=postgres >>$CSQL_CONFIG_FILE
   else
      echo TARGET_DATABASE=mysql >>$CSQL_CONFIG_FILE
   fi
   DS=$DSN
else
   echo DSN=$DSN >>$CSQL_CONFIG_FILE
   echo DBUSER=$DBUSER >>$CSQL_CONFIG_FILE
   echo PASSWORD=$PASSWORD >>$CSQL_CONFIG_FILE
   echo TARGET_DATABASE=oracle >>$CSQL_CONFIG_FILE
   DS="$DSN $DBUSER $PASSWORD"
fi
$CSQL_INSTALL_ROOT/bin/csqlsqlserver >/dev/null 2>&1 &
pid=$!
sleep 3
${REL_PATH}/selecttest2na
if [ $? -ne 0 ]
then
   kill -9 $pid
   exit 1;
fi
rm -f /tmp/csql.conf
kill -9 $pid 
exit 0;
