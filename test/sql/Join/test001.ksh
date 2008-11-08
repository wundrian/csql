#!/bin/sh
# Test Case 
# 1.	Create t1 table with 5  records in csql database.
# 	select t1.f1 from t1;
#	select t1.notexist from t1;
#	

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Join
fi

echo " select t1.f1 from t1;"  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join1.sql 
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
  exit 2;
fi
  
echo " select t1.notexist from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join2.sql  
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
  exit 2;
fi


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
 exit 0;
