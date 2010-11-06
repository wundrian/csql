#!/bin/ksh
#Testing DATE_ADD function by adding month value
# Create table t1(f1 date, f2 date);
# insert into t1 values('2001-05-01', '2001-05-01');
# insert into t1 values('2001-06-01', '2001-06-01');
# insert into t1 values('2001-07-01', '2002-07-01');
# insert into t1 values('2001-08-01', '2002-08-01');
# insert into t1 values('2001-09-01', '2002-09-01');
# select * from t1;
# select * from t1 where date_add(f1 interval 5 month) < '2001-12-01';
# select * from t1 where date_add(f1 interval 6 month) = '2002-01-01';
# select * from t1 where date_add(f1 interval 18 month)>= '2003-01-01';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_month.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_month.sql
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
