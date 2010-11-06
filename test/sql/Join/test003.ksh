#!/bin/ksh
# Test Case 
# 	Create t1(6 rec),t2(6 rec),t3(6 rec),t4(2 rec),t5(2 rec) table.
# 	Select  * from t1,t2,t3,t4,t5;
#       select * from t1,t2 where t1.f1>100;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2t3t4t5.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join3.sql  
if [ $? -ne 0 ]
then
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3t4t5.sql > /dev/null 2>&1
  exit 1;
fi

  
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2t3t4t5.sql > /dev/null 2>&1
  exit 0;

