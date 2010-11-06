#!/bin/ksh
# Testing limit and offset on GROUP BY and HAVING.
#
CREATEFILE=${PWD}/sql/Limit/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Limit
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/groupby.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/groupby.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

exit 0;
