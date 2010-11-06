#!/bin/ksh
# Group by and aggregate function of projection list cannot applied on same field
#

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

echo "create table t1 (f1 int,f2 int,f3 int);" >${REL_PATH}/grp_agg.sql
echo "insert into t1 values(1,10,100);" >>${REL_PATH}/grp_agg.sql
echo "insert into t1 values(2,20,100);" >>${REL_PATH}/grp_agg.sql
echo "insert into t1 values(1,30,200);" >>${REL_PATH}/grp_agg.sql
echo "insert into t1 values(3,40,200);" >>${REL_PATH}/grp_agg.sql
echo "insert into t1 values(2,50,300);" >>${REL_PATH}/grp_agg.sql
echo "insert into t1 values(1,60,300);" >>${REL_PATH}/grp_agg.sql
echo "select * from t1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,MAX(f1) from t1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,COUNT(f1) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,MIN(f1) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,MAX(f1) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,SUM(f1) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,AVG(f1) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql
echo "select f1,MAX(f2) from t1 group by f1;" >>${REL_PATH}/grp_agg.sql


$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/grp_agg.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   rm -f ${REL_PATH}/grp_agg.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/grp_agg.sql
exit 0;
