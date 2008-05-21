#!/bin/sh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

mv ~/.odbc.ini /tmp

touch ~/.odbc.ini

$CSQL_INSTALL_ROOT/bin/csqlserver -c

mv /tmp/.odbc.ini ~/

exit 0;
