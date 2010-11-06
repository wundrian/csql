#!/bin/ksh
#Testing TIMESTAMP_SUB function by adding day value
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2001-01-01 01:01:01', '2001-05-10 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-03-10 01:01:01');
# insert into t1 values('2003-01-01 01:01:01', '2003-03-10 01:01:01');
# insert into t1 values('2004-01-01 01:01:01', '2004-03-10 01:01:01');
# insert into t1 values('2005-01-01 01:01:01', '2005-02-10 01:01:01');
# select * from t1;
# select * from t1 where timestamp_sub(f2 interval 15 day) ='2001-04-25 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 15 day)<='2002-02-23 01:01:01'; 
# select * from t1 where timestamp_sub(f2 interval 15 day)>='2003-02-23 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 15 day) ='2004-02-24 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 15 day)!='2005-01-26 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 45 day) ='2004-12-27 01:01:01'; 
# select * from t1 where timestamp_sub(f2 interval 45 day)!='2004-12-27 01:01:01';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_sub_day.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_sub_day.sql
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
