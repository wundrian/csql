#!/bin/sh
#Test case
#Default autocommit mode
#Insert 4 records . Update records providing some condition,Disconnect csql and then reconnect csql. Check changes made by update should be reflected on the records.
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/autocommit1.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/autocommit4.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop2.sql
if [ $? -ne 0 ]
then
   exit 1;
fi

