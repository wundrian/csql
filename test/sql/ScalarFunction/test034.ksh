#!/bin/ksh
#Testing extract month from date
# Create table t1(f1 date, f2 date);
# insert into t1 values('2001-01-01', '2001-01-01');
# insert into t1 values('2001-01-01', '2001-01-03');
# insert into t1 values('2001-01-03', '2002-02-03');
# insert into t1 values('2001-01-01', '2002-02-04');
# insert into t1 values('2001-01-01', '2003-03-05');
# select * from t1;
# select * from t1 where extract(month from f2) = 02;
# select * from t1 where extract(month from f2) < 02;
# select * from t1 where extract(month from f2)<= 02;
# select * from t1 where extract(month from f2) > 02;
# select * from t1 where extract(month from f2)>= 02;
# select * from t1 where extract(month from f2)!= 02;
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_month_from_date.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/extract_month_from_date.sql
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
