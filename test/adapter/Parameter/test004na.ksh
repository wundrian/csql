#!/bin/ksh

CSQL_CONF=${PWD}/adapter/Parameter/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/adapter/Parameter
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp/csql.conf
echo CSQL_SQL_SERVER=true >>/tmp/csql.conf
#echo PORT= >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"

$CSQL_INSTALL_ROOT/bin/csqlsqlserver >/dev/null 2>&1 &
pid=$!
sleep 5 
${REL_PATH}/paratest4na
if [ $? -ne 0 ]
then
   kill -9 $pid
   exit 1;
fi
rm -f /tmp/csql.conf
kill -9 $pid 
exit 0;
