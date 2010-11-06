#!/bin/ksh


CSQL_CONF=${PWD}/phptests/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/phptests
fi

php $REL_PATH/odbc_statistics.php
if [ $? -ne 0 ]
then
    exit 50;
fi
exit 0;


