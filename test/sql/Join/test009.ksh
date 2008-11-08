#!/bin/sh
# Test Case 
# 6.	Create t1,t2 table with 5 each records in csql database.
# 	select * from t1, notexist;
#	select * from t1,t2 where t1.f1 = t2.notexist

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi


echo "select * from t1,t2 where t1.f1=t2.notexist:" 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join13.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
exit 0;

