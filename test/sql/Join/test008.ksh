#!/bin/sh
# Test Case 
# 5.
#	Create t1,t2,t3 table with 5 each records in csql database.
#	select t1.f1, t2.f1, t3.f1 from t1,t2,t3 where t1.f2= t2.f2 or t1.f1 >100

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2t3.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
 fi

echo "select t1.f1, t2.f1, t3.f1 from t1,t2,t3 where t1.f2= t2.f2 or t1.f1 >100:"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join11.sql
 if [ $? -ne 0 ]
   then
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
 exit 4;
 fi

  
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3.sql > /dev/null 2>&1
  exit 0;

