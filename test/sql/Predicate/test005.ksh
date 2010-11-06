#!/bin/ksh
# Testing Relational Operators(,<,>,<,>=,!=) with varchar in Update statement. ( )
# REATE TABLE t1 (f1 INT , f2 VARCHAR (12));
# NSERT INTO t1 VALUES(1, 'ABCDE');
# NSERT INTO t1 VALUES(2, 'ABCDF');
# NSERT INTO t1 VALUES(3, 'ABCDG');
# NSERT INTO t1 VALUES(4, 'ABCDH');
# NSERT INTO t1 VALUES(5, 'ABCDI');
# NSERT INTO t1 VALUES(6, 'NBCDE');
# NSERT INTO t1 VALUES(7, 'NBCDF');
# NSERT INTO t1 VALUES(8, 'NBCDG');
# NSERT INTO t1 VALUES(9, 'NBCDH');
# NSERT INTO t1 VALUES(10, 'NBCDI');
# est the below Update statements return proper result set or not.
# elect * from t1;
# pdate t1 set f1=100, f2='Lakshya10' where f2='NBCDI';
# pdate t1 set f1=85, f2='Lakshya8.5' where f2>='NBCDG';
# pdate t1 set f1=70, f2='Lakshya7' where f2>'NBCDE';
# pdate t1 set f1=15, f2='Lakshya1.5' where f2<'ABCDG';
# update t1 set f1=30, f2='Lakshya3' where f2<='ABCDH';
# update t1 set f1=55, f2='Lakshya5.5' where f2!='Lakshya8.5';
#
CREATEFILE=${PWD}/sql/Predicate/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Predicate
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_relational_upd.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_relational_upd.sql 
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
