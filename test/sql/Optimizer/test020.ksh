#!/bin/ksh
# Left OuterJoin test using explain plan(Hash index on both table).
# create table t1(f1 int, f2 int);
# create index hashidxt1f1 on t1(f1) hash;
# create index hashidxt1f2 on t1(f2) hash;
# create table t2(f1 int, f2 int);
# create index hashidxt2f1 on t2(f1) hash;
# create index hashidxt2f2 on t2(f2) hash;
# explain plan select * from t1,t2;
# explain plan select * from t1 left join t2 on t1.f1=t2.f1;
# explain plan select * from t1 left join t2 on t1.f1<=t2.f1;
# explain plan select * from t1 left join t2 on t1.f1!=t2.f1;
#
QUITFILE=${PWD}/sql/Optimizer/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Optimizer
fi

echo "drop table t1;" >${REL_PATH}/dropt1t2.sql
echo "drop table t2;" >>${REL_PATH}/dropt1t2.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/leftjoin_hash_int.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/leftjoin_hash_int.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1t2.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql 
rm -f ${REL_PATH}/dropt1t2.sql

exit 0;

