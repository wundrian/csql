#!/bin/ksh
#Test Case
# Create table t1 with 5 records in csql database.
# select query with expression in aggregate
# as we do not support expressions in aggregate, it should give syntax error


#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi


echo "select sum(12*f1) where f4='BBB':"
$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/aggsum3.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 2;
 fi



$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
exit 0;

