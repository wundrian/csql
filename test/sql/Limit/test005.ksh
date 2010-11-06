#!/bin/ksh
# Testing limit and offset on self joined table.
#
CREATEFILE=${PWD}/sql/Limit/dropt1.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Limit
fi


$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selfjoin1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropemp10.sql
   exit 1;
fi

echo "drop table emp10;" >${REL_PATH}/dropemp10.sql 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropemp10.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/dropemp10.sql
   exit 2;
fi
rm -f ${REL_PATH}/dropemp10.sql
exit 0;
