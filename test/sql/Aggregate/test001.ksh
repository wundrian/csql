#!/bin/sh
#Test Case
#1.	Create table t1 with 5 records in csql database.
#	select query with count,sum,avg,min,max.

#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi

echo "select count(f1) from nonExistTab :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggcount1.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
     exit 2;
fi 

echo "select count(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggcount2.sql 
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 3;
fi  

echo "select sum(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggsum1.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 4;
fi  

echo "select avg(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggavg1.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 5;
fi        

echo "select min(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmin1.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 6;
 fi   

echo "select max(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmax1.sql
if [ $? -ne 0 ]
   then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
     exit 6;
  fi    

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
exit 0;

