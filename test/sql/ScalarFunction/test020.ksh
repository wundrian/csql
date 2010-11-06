#!/bin/ksh
#Testing TIMESTAMP_ADD function by adding second value
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2001-01-01 01:01:01', '2001-01-25 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-02-25 01:01:01');
# insert into t1 values('2003-01-01 01:01:01', '2003-02-25 01:01:01');
# insert into t1 values('2004-01-01 01:01:01', '2004-02-25 01:01:01');
# insert into t1 values('2005-01-01 01:01:01', '2005-11-25 01:01:01');
# select * from t1;
# select * from t1 where timestamp_add(f2 interval 14644 second) ='2003-02-25 05:05:05';
# select * from t1 where timestamp_add(f2 interval 14644 second)<='2003-02-25 05:05:05';
# select * from t1 where timestamp_add(f2 interval 14644 second) >'2003-02-25 05:05:05';
# select * from t1 where timestamp_add(f2 interval 878644 second) ='2001-02-04 05:05:05';
# select * from t1 where timestamp_add(f2 interval 878644 second) ='2002-03-07 05:05:05';
# select * from t1 where timestamp_add(f2 interval 878644 second) ='2004-03-06 05:05:05';
# select * from t1 where timestamp_add(f2 interval 3470644 second) ='2006-01-04 05:05:05';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_add_second.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_add_second.sql
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
