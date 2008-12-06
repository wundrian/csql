#!/bin/sh
# Test Case 
# 11.	Create emp table with 5 fields & dept table with 3 fields and insert        3 records in it. 

#	(a)select t11.f1,t11.f2,t13.f7,t13.f8 from t11,t13 where t11.f5=t13.f8;
#	(b)select f1,f3,f7,f8 from t11,t13 where t11.f5=t13.f8;
#	(c)select t11.f1,t11.f2,t12.f1,t12.f2 from t11,t12,t13 where t13.f8 > t11.f5;
#	(d)select f1,f3,f7,f8 from t11,t13 where t13.f8 < t11.f5;
#	(e)select f1,f3,f7,f8 from t11,t13 where f5 > f8;

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


echo "select t11.f1,t11.f2,t13.f7,t13.f8 from t11,t13 where t11.f5=t13.f8;" 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join22.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
     exit 2;
fi


echo " select f1,f3,f7,f8 from t11,t13 where t11.f5=t13.f8;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join23.sql
if [ $? -ne 0 ]
  then
      $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
      exit 3;
fi   

echo "select t11.f1,t11.f2,t12.f1,t12.f2 from t11,t12,t13 where t13.f8 > t11.f5;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join24.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
    exit 4;
fi

echo "select f1,f3,f7,f8 from t11,t13 where t13.f8 < t11.f5;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join25.sql
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
     exit 5;
fi

echo "select f1,f3,f7,f8 from t11,t13 where f5 > f8;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join26.sql
if [ $? -ne 0 ]
   then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
     exit 6;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t13.sql > /dev/null 2>&1
exit 0;

