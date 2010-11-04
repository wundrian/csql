#!/bin/ksh

CSQL_CONF=${PWD}/adapter/Connect/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/adapter/Connect
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
#echo PORT=6011 >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

if [ -z "$DBUSER" ]
then
   echo DSN=$DSN >>$CSQL_CONFIG_FILE
   DS=$DSN
else
   echo DSN=$DSN >>$CSQL_CONFIG_FILE
   echo DBUSER=$DBUSER >>$CSQL_CONFIG_FILE
   echo PASSWORD=$PASSWORD >>$CSQL_CONFIG_FILE
   DS="$DSN $DBUSER $PASSWORD"
fi

$CSQL_INSTALL_ROOT/bin/csqlsqlserver >/dev/null 2>&1 &
pid=$!
sleep 3
${REL_PATH}/conntest11na
if [ $? -ne 0 ]
then
#   kill -9 $pid
#   kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
   exit 1;
fi
rm -f /tmp/csql.conf
#kill -9 $pid 
#ipcrm -M 2266 -M 3366
#kill `ps -el | grep csqlsqlserver | gawk -F" " '{ print $4 }'`
exit 0;
