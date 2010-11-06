#!/bin/ksh
# Testing self join 
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Join
fi
echo "drop table emp10;" > ${REL_PATH}/dropp_emp10.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selfjoin1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_emp10.sql
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_emp10.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/dropp_emp10.sql
   exit 3;
fi
rm -f ${REL_PATH}/dropp_emp10.sql
exit 0;
