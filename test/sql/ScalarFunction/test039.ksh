#!/bin/ksh
#Testing extract year,month,day from timestamp
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2001-01-01 01:01:01', '2001-10-05 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-20-10 02:02:02');
# insert into t1 values('2003-01-03 01:01:01', '2003-30-15 12:30:30');
# insert into t1 values('2004-01-01 01:01:01', '2004-40-20 22:58:58');
# insert into t1 values('2005-01-01 01:01:01', '2005-50-25 23:59:59');
# select * from t1;
# select * from t1 where extract(year from f2) =2003;
# select * from t1 where extract(year from f2)<=2003;
# select * from t1 where extract(year from f2) >2003;
# select * from t1 where extract(year from f2)!=2003;

# select * from t1 where extract(month from f2) =30;
# select * from t1 where extract(month from f2) <30;
# select * from t1 where extract(month from f2)>=30;
# select * from t1 where extract(month from f2)!=30;

# select * from t1 where extract(day from f2) =30;
# select * from t1 where extract(day from f2) <30;
# select * from t1 where extract(day from f2) >30;
# select * from t1 where extract(day from f2)<>30;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_yearmonthday_from_timestamp.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_yearmonthday_from_timestamp.sql
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
