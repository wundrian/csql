#!/bin/ksh
# Testing simple left join on two table with integers
#
CREATEFILE=${PWD}/sql/OuterJoin/dropt1t2.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/OuterJoin
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/simpleleft.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
