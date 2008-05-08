#!/bin/sh
# TestCase:

CSQL_CONFIG_FILE=$CSQL_SRCROOT/test/csql.conf



#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
executable=${PWD}/dbapi/Connection/serverOff
REL_PATH=.
if [ -s "$executable" ]
then
    REL_PATH=${PWD}/dbapi/Connection
fi

${REL_PATH}/serverOff

if [ $? -ne 0 ]
then
   exit 1;
fi

exit 0
