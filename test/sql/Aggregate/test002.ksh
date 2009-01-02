#!/bin/sh
#Test Case
#2.	Create table t1 with 5 records in csql database.
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

echo "select count(t1.f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggcount3.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
     exit 2;
fi 

echo "select count(*) from t1 where f4='AAA':"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggcount5.sql
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
   exit 3;
 fi


echo "select sum(t1.f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggsum2.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 4;
fi  



echo "select avg(t1.f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggavg2.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 5;
fi        

echo "select min(t1.f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmin2.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 6;
 fi   

echo "select min(f4) from t1:"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmin5.sql
if [ $? -ne 0 ]
   then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
     exit 7;
  fi


echo "select max(t1.f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmax2.sql
if [ $? -ne 0 ]
   then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
     exit 6;
  fi    

echo "select max(f4) from t1:"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggmax3.sql
if [ $? -ne 0 ]
   then
      $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
      exit 7;
   fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
exit 0;

