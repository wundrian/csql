#!/bin/sh
#Test Case
#4.	Create table t1 with 5 records in csql database.
#	select query with count,sum,avg,min,max.

#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggregate4.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 2;
fi 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
exit 0;

