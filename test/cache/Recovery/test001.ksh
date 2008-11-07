#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

CSQL_CONF=${PWD}/cache/Recovery/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >> $CSQL_CONFIG_FILE

isql $DSN < $REL_PATH/drop.sql > /dev/null 2>&1
isql $DSN < $REL_PATH/createt1.sql > /dev/null 2>&1

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "1:t1 NULL NULL NULL" > /tmp/csql/csqltable.conf

mv ~/.odbc.ini  /tmp

touch ~/.odbc.ini

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
sleep 3
if [ $? -ne 0 ]
then
    mv /tmp/.odbc.ini ~
    isql $DSN < $REL_PATH/drop.sql > /dev/null 2>&1
    exit 1;
fi

mv /tmp/.odbc.ini  ~
isql $DSN < $REL_PATH/drop.sql > /dev/null 2>&1

exit 0;
