#!/bin/sh
# Test Case 
# 3.	Create t1,t2,t3,t4,t5 table with in  csql database.
# 	Select  * from t1,t2,t3,t4,t5;

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

