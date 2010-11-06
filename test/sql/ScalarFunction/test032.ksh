#!/bin/ksh
#Testing TIMESTAMP_DIFF function using second
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2002-01-01 01:01:01', '2002-01-01 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-01-01 01:01:05');
# insert into t1 values('2002-01-01 01:01:01', '2002-01-01 01:05:05');
# insert into t1 values('2002-01-01 01:01:01', '2002-01-01 05:05:05');
# insert into t1 values('2002-01-01 01:01:01', '2002-01-03 05:05:05');
# insert into t1 values('2002-01-01 01:01:01', '2002-03-03 05:05:05');
# insert into t1 values('2002-01-01 01:01:01', '2004-03-01 05:05:05');
# select * from t1;
# select * from t1 where timestamp_diff(second,f1,f2) =0;
# select * from t1 where timestamp_diff(second,f2,f1) =4;
# select * from t1 where timestamp_diff(second,f2,f1)<=244;
# select * from t1 where timestamp_diff(second,f2,f1) =14644;
# select * from t1 where timestamp_diff(second,f2,f1)>=14644;
# select * from t1 where timestamp_diff(second,f2,f1) =187444;
# select * from t1 where timestamp_diff(second,f2,f1) =5285044;
# select * from t1 where timestamp_diff(second,f2,f1)!=5285044;
# select * from t1 where timestamp_diff(second,f2,f1) =68270644;
#
CREATEFILE=${PWD}/sql/ScalarFunction/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/ScalarFunction
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_diff_second.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_diff_second.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/dropt1.sql
exit 0;
