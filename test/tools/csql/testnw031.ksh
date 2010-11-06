#!/bin/ksh
# network
# Testing Autoincrement field on TINYINT Datatype
# Same is at test095.ksh for without network
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/auto_increment_TINYINT.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop10.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop10.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

