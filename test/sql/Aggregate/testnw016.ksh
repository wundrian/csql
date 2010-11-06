#!/bin/ksh
# Create two tables, having same fieldnames say f1,f2 in both the tables.
# Testing projection fieldname without tablename in joinint the two table.
# for ex : select f1 from t1,t2;
#          select sum(f2) from t1,t2;
# 
#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/nulltest1.sql
if [ $? -ne 0 ]
 then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/projfield.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql
    exit 2;
 fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql 
exit 0;

