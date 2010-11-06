#!/bin/ksh
#Testing TIMESTAMP_DIFF function using month
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2002-01-01 01:01:01', '2002-01-01 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-02-03 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-03-01 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2004-02-01 01:01:01');
# insert into t1 values('2002-01-10 01:01:01', '2004-02-01 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2004-03-01 01:01:01');
# insert into t1 values('2002-01-10 01:01:01', '2004-03-01 01:01:01');
# select * from t1;
# select * from t1 where timestamp_diff(month,f1,f2)=0;
# select * from t1 where timestamp_diff(month,f2,f1)<=2;
# select * from t1 where timestamp_diff(month,f2,f1)=25;
# select * from t1 where timestamp_diff(month,f2,f1)>=25;
# select * from t1 where timestamp_diff(month,f2,f1)=26;
# select * from t1 where timestamp_diff(month,f2,f1)!=26;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_diff_month.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_diff_month.sql
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
