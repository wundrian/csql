#!/bin/ksh
# Test Case 
#Create t11 table with 5 fields f1,f2,f3,f4,f5
#Create t13 table with 2 fields f7,f8 
#Insert 3 records in each. 
#(a)select t11.f1,t11.f2,t13.f7,t13.f8 from t11,t13 where t11.f5=t13.f8;
#(b)select f1,f3,f7,f8 from t11,t13 where t11.f5=t13.f8;
#(c)select t11.f1,t11.f2,t12.f1,t12.f2 from t11,t12,t13 where t13.f8 > t11.f5;
#(d)select f1,f3,f7,f8 from t11,t13 where t13.f8 < t11.f5;
#(e)select f1,f3,f7,f8 from t11,t13 where f5 > f8;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11t13.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi


 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join9.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
     exit 2;
fi




$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
exit 0;

