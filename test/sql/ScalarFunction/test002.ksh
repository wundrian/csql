#!/bin/ksh
# Testing DATE_DIFF function
# Create table t1(f1 date, f2 date);
# insert into t1 values('01:01:01', '01:01:03');
# insert into t1 values('01:01:01', '01:02:01');
# insert into t1 values('01:01:01', '01:03:01');
# insert into t1 values('01:01:01', '02:01:01');
# insert into t1 values('01:01:01', '02:02:02');
# select * from t1 where time_diff(f2,f1)=2;
# select * from t1 where time_diff(f1,f2)=2;
# select * from t1 where time_diff(f2,f1)=60;
# select * from t1 where time_diff(f2,f1)=120;
# select * from t1 where time_diff(f2,f1)=3600;
# select * from t1 where time_diff(f2,f1)=3661;
# select * from t1 where time_diff(f2,f1)<120;
# select * from t1 where time_diff(f2,f1)<=120;
# select * from t1 where time_diff(f2,f1)>120;
# select * from t1 where time_diff(f2,f1)>=120;
# select * from t1 where time_diff(f2,f1)!=120;
# select * from t1 where time_diff(f2,'01:01:01')=2;
# select * from t1 where time_diff(f2,'01:01:01')>=120;
# select * from t1 where time_diff(f2,'01:01:01')!=3600;
# select * from t1 where time_diff('01:01:02','01:01:01')=1;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/time_diff.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/time_diff.sql
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
