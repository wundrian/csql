#!/bin/ksh
#Testing extract hour,minute,second from timestamp
# Create table t1(f1 timestamp, f2 timestamp);
# insert into t1 values('2001-01-01 01:01:01', '2001-01-05 01:01:01');
# insert into t1 values('2002-01-01 01:01:01', '2002-04-10 02:02:02');
# insert into t1 values('2003-01-03 01:01:01', '2003-07-15 12:30:30');
# insert into t1 values('2004-01-01 01:01:01', '2004-10-20 22:58:58');
# insert into t1 values('2005-01-01 01:01:01', '2005-12-25 23:59:59');
# select * from t1;
# select * from t1 where extract(hour from f2) =12;
# select * from t1 where extract(hour from f2)<=12;
# select * from t1 where extract(hour from f2) >12;
# select * from t1 where extract(hour from f2)!=12;

# select * from t1 where extract(minute from f2) =30;
# select * from t1 where extract(minute from f2) <30;
# select * from t1 where extract(minute from f2)>=30;
# select * from t1 where extract(minute from f2)!=30;

# select * from t1 where extract(second from f2) =30;
# select * from t1 where extract(second from f2) <30;
# select * from t1 where extract(second from f2) >30;
# select * from t1 where extract(second from f2)<>30;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_hourminutesecond_from_timestamp.sql

else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_hourminutesecond_from_timestamp.sql

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
