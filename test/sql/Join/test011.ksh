#!/bin/ksh
# Test Case 
# Create t11 table with 5 fields(f1,f2,f3,f4,f5)
# Create t12 with 3 fields(f1,f2,f3)
# Create t13 with 2 fields(f7,f8)
# Insert 3 records in each.
# (a)select f1,f7 from t12,t11;
# (b)select t11.f1,t12.f7 from t13,t11;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11t12t13.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi



$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join11.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
     exit 2;
fi

   

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12t13.sql > /dev/null 2>&1
exit 0;

