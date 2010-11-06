#!/bin/ksh
# explain plan for is null and is not null operator and composite hash index on mixed datatypes 
#create table t1(f1 int, f2 int, f3 varchar(20),f4 date);
#create index idx on t1(f3,f4,f2) hash;
#explain plan select * from t1 where f2 is null;
#explain plan select * from t1 where f2 is not null;
#explain plan select * from t1 where f2 is null and f3 is not null;
#explain plan select * from t1 where f1 is null or f2 is not null or f3 is null or f4 is not null;
#explain plan select * from t1 where f1 is null and f2 is not null and f3 is null and f4 is not null;
#
QUITFILE=${PWD}/sql/Optimizer/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Optimizer
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/explainplan_isnull_isnotnull.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/explainplan_isnull_isnotnull.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

