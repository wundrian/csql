#!/bin/sh
#Test Case
#6.	Create table t1 with 5 records in csql database.
#	select query with count,sum,avg,min,max and Group By.

#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi

echo "select min(t1.f2) from t1 group by t1.f1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby3.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 2;
fi 

echo "select f1, avg(t1.f2) from t1 group by t1.f1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby4.sql 
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
    exit 3;
fi  

echo "select f1, sum(f2) from t1 group by f3 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby5.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
    exit 4;
fi  

echo "select f1, sum(f2) from t1 group by notexist :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby6.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
    exit 5;
fi        

echo "select f1, sum(f2) from t1 group by notexist.f2:"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby7.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
    exit 6;
 fi   

echo "select f1, sum(f2) from t1 group by t2.f2 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby8.sql
if [ $? -ne 0 ]
   then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 6;
  fi    

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
exit 0;

