#!/bin/sh
# Test Case 
# 10.	Create t1 table with 5 fields, and insert 3 records in it. 

#	(a)select * from t11 where t1.f1=2;
#	(b) select * from t11 where t1.f1=t1.f1;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi


 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join7.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drot11.sql > /dev/null 2>&1
     exit 2;
fi



$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11.sql > /dev/null 2>&1
exit 0;

