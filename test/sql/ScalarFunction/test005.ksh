#!/bin/ksh
#Testing DATE_ADD function by adding day value
# Create table t1(f1 date, f2 date);
# insert into t1 values('2008-01-20', '2010-01-01');
# insert into t1 values('2009-04-20', '2011-02-01');
# insert into t1 values('2010-02-27', '2010-03-01');
# insert into t1 values('2011-02-28', '2013-02-01');
# insert into t1 values('2012-02-29', '2014-01-01');
# select * from t1;
# select * from t1 where date_add(f1 interval 2 day) = '2010-03-01';
# select * from t1 where date_add(f1 interval 15 day) <= '2008-02-04';
# select * from t1 where date_add(f1 interval 15 day) >= '2009-05-05';
# select * from t1 where date_add(f1 interval 40 day) <= '2008-03-01';
# select * from t1 where date_add(f1 interval 40 day) >= '2009-05-30';
# select * from t1 where date_add(f1 interval 365 day) <= '2010-04-20';
# select * from t1 where date_add(f1 interval 366 day) >= '2010-04-21';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_day.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_day.sql
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
