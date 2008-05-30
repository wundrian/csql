#!/bin/sh
#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
executable=${PWD}/dbapi/Table/insert
CSQL_CONF=${PWD}/dbapi/Table/csql.conf
REL_PATH=.
if [ -s "$executable" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/dbapi/Table
fi

export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

$REL_PATH/insert
if [ $? -ne 0 ]
then
    exit 2;
fi

kill -9 $pid 
if [ $? -ne 0 ]
then
    exit 3;
fi
ipcrm -M 7117 -M 1771

exit 0;
