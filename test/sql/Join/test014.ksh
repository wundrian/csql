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

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11t12t13.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi


echo "select f1,f7 from t12,t11;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join29.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drot11t12t13.sql > /dev/null 2>&1
     exit 2;
fi

echo " select t11.f1,t12.f7 from t13,t11;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join30.sql
if [ $? -ne 0 ]
  then
      $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
      exit 3;
fi   

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
exit 0;

