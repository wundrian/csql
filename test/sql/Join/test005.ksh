#!/bin/sh
# Test Case 
# 5.
#	Create t1,t2,t3 table with 5 each records in csql database.
# 	select * from t1,t2,t3 where t1.f2= t2.f2 and t1.f3 = t3.f2
#	select * from t1,t2,t3 where t1.f2= t2.f2 or t1.f3 = t3.f2

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
 then
REL_PATH=`pwd`/sql/Join
fi

echo "select * from t1,t2,t3 where t1.f2= t2.f2 and t1.f3 = t3.f2:"  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2t3.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join9.sql 
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
  exit 2;
fi
  
echo "select * from t1,t2,t3 where t1.f2= t2.f2 or t1.f3 = t3.f2:"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join10.sql 
if [ $? -ne 0 ]
 then
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
  exit 3;
 fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
exit 0;

