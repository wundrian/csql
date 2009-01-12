#!/bin/sh
# Test Case 
# 10.	Create emp table with 5 fields, and insert 3 records in it. 

#	(a)select f1,f7 from t12,t11;
#	(b)select t11.f1,t12.f7 from t13,t11;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join31.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
