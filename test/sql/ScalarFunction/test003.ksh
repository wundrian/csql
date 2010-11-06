#!/bin/ksh
#Testing DATE_ADD function by adding year value
# Create table t1(f1 date, f2 date);
# insert into t1 values('2001-01-01', '2005-01-01');
# insert into t1 values('2002-01-01', '2006-01-01');
# insert into t1 values('2003-01-01', '2007-01-01');
# insert into t1 values('2004-01-01', '2009-01-01');
# insert into t1 values('2005-01-01', '2010-01-01');
# select * from t1;
# select * from t1 where date_add(f1 interval 4 year) = '2007-01-01';
# select * from t1 where date_add(f1 interval 4 year) = f2;
# select * from t1 where date_add(f1 interval 4 year) = f2;
# select * from t1 where date_add(f1 interval 4 year) <= '2007-01-01';
# select * from t1 where date_add(f1 interval 4 year) > '2007-01-01';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_year.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/date_add_year.sql
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
