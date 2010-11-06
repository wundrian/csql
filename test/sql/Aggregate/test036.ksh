#!/bin/ksh
# Testing Join on 5 sales tables.
# select t1.f1,t1.f2,count(t1.f3),count(t2.f3) from t1,t2 group by t1.f1,t1.f2 ;
# This statement should  work properly.
# select t1.f1,t1.f2,count(t1.f3),count(t2.f3) from t1,t2 group by t1.f1,t1.f2 having avg(t1.f2)<70;
# This statement should not work becoz expression in having clause not present in projection list. 
#

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/innerjoin_aggregate.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/innerjoin_aggregate.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
