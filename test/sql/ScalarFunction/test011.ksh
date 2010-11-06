#!/bin/ksh
#Testing TIME_ADD function by adding second value
# Create table t1(f1 time, f2 time);
# insert into t1 values('01:01:01', '01:30:01');
# insert into t1 values('02:01:01', '02:30:01');
# insert into t1 values('03:01:01', '03:30:01');
# insert into t1 values('04:01:01', '04:30:01');
# insert into t1 values('05:01:01', '05:30:01');
# select * from t1;
# select * from t1 where time_add(f2 interval 1800 second)  = '04:00:01';
# select * from t1 where time_add(f2 interval 1800 second) <= '04:00:01';
# select * from t1 where time_add(f2 interval 1800 second) >= '04:00:01';
# select * from t1 where time_add(f2 interval 14400 second)  = '07:30:01';
# select * from t1 where time_add(f2 interval 14400 second) <= '07:30:01';
# select * from t1 where time_add(f2 interval 72000 second) >= '21:30:01';
# select * from t1 where time_add(f2 interval 72000 second) < '21:30:01';

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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/time_add_second.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/time_add_second.sql
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
