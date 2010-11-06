#!/bin/ksh
# Testing LIKE, IN Operators with varchar in Update Statement. ( )
# CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
# INSERT INTO t1 VALUES(1, 'ABCDE');
# INSERT INTO t1 VALUES(2, 'ABCDF');
# INSERT INTO t1 VALUES(3, 'NBCDGH');
# INSERT INTO t1 VALUES(4, 'NABCDIJ');
# INSERT INTO t1 VALUES(5, 'PQRST');
# INSERT INTO t1 VALUES(6, 'NIHAR');
# INSERT INTO t1 VALUES(7, 'RAHUL');
# Test the below Update statements return proper result set or not.
# select * from t1;
# Update t1 set f1=10, f2='CSQL1' where f2 LIKE 'ABCD%';
# Update t1 set f1=25, f2='CSQL2.5' where f2 LIKE '_BCD%';
# Update t1 set f1=56, f2='CSQL6.5' where f2 in ('NIHAR','rahul','CSQL1');
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_like_in_upd.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_like_in_upd.sql 
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
