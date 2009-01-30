#!/bin/sh
# Test Case 
# 10.	Create emp table with 5 fields, and insert 3 records in it. 

#	(a)select * from t11,t12,t13 where t12.f1=t13.f8 and t13.f7=t11.f1;
#	(b)select * from t11,t12,t13 where t12.f1=t13.f8 or t13.f7=t11.f1;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11t12t13.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi




$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join10.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
     exit 2;
fi

   

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
exit 0;

