#!/bin/ksh
#Test Case

# Create table t1 with 5 records in csql database.
# Insert 10-11 records with null value in some of the records.
# Test group by all aggregate functions on the fields having null values
#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/nulltest2.sql
if [ $? -ne 0 ]
 then
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/aggregate_groupby1.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql
    exit 2;
 fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
exit 0;

