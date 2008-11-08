#!/bin/sh
# Test Case 
# 2.	Create t1,t2 table with 5 each records in csql database.
# 	Select * from t1,t2 where where t1.f1 >100
#	select * from t1, t2 where t1.f1 >100 or t2.f1 <100
#	

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

echo "select * from t1,t2 where t1.f1>100:"  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join4.sql 
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
  exit 2;
fi
  
echo "select * from t1,t2 where t1.f1>100 or t2.f1<100:"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join5.sql 
if [ $? -ne 0 ]
 then
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
  exit 3;
 fi


  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
  exit 0;

