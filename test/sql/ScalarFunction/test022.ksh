#!/bin/ksh
#Testing TIMESTAMP_SUB function by adding month value
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2001-01-01 01:01:01', '2010-08-01 02:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2010-09-01 01:01:01');
# insert into t1 values('2003-01-01 01:01:01', '2010-10-01 01:01:01');
# insert into t1 values('2004-01-01 01:01:01', '2010-11-01 01:01:01');
# insert into t1 values('2005-01-01 01:01:01', '2010-12-01 01:01:01');
# select * from t1;
# select * from t1 where timestamp_sub(f2 interval 10 month) ='2009-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 10 month)<='2009-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 10 month) >'2009-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 10 month)!='2009-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 130 month) ='1999-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 130 month)<='1999-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 130 month) >'1999-12-01 01:01:01';
# select * from t1 where timestamp_sub(f2 interval 130 month)!='1999-12-01 01:01:01';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_sub_month.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/timestamp_sub_month.sql
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
