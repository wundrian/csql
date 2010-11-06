#!/bin/ksh
# Testing DATE_DIFF function
# Create table t1(f1 date, f2 date);
# insert into t1 values('2001-01-01', '2001-01-03');
# insert into t1 values('2001-01-01', '2001-02-01');
# insert into t1 values('2001-01-01', '2001-03-01');
# insert into t1 values('2001-01-01', '2002-01-01');
# insert into t1 values('2001-01-01', '2002-02-02');
# select * from t1;
# select * from t1 where date_diff(f2,f1)=2;
# select * from t1 where date_diff(f1,f2)=2;
# select * from t1 where date_diff(f2,f1)=31;
# select * from t1 where date_diff(f2,f1)=59;
# select * from t1 where date_diff(f2,f1)=365;
# select * from t1 where date_diff(f2,f1)=397;
# select * from t1 where date_diff(f2,f1)<59;
# select * from t1 where date_diff(f2,f1)<=59;
# select * from t1 where date_diff(f2,f1)>59;
# select * from t1 where date_diff(f2,f1)>=59;
# select * from t1 where date_diff(f2,f1)!=59;
# select * from t1 where date_diff(f2,'2001-01-01')=2;
# select * from t1 where date_diff(f2,'2001-01-01')>=59;
# select * from t1 where date_diff(f2,'2001-01-01')!=365;
# select * from t1 where date_diff('2001-01-02','2001-01-01')=1;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_diff.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_diff.sql
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
