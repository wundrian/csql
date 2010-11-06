#!/bin/ksh
# Testing Logical Operators(AND, OR, NOT) with varchar using Update statement. (sql/Predicate/test004.ksh)
# Create table t1(f1 varchar(10), f2 char(10), f3 varchar(10), f4 int);
# Insert into t1 values('CSQL1', 'LAKS1','BBSR1',10);
# Insert into t1 values('CSQL1', 'LAKS1','BBSR2',20);
# Insert into t1 values('CSQL1', 'LAKS2','BBSR3',30);
# Insert into t1 values('CSQL1', 'LAKS2','BBSR4',40);
# Insert into t1 values('CSQL2', 'LAKS3','BBSR5',50);
# Insert into t1 values('CSQL2', 'LAKS3','BBSR6',60);
# Insert into t1 values('CSQL2', 'LAKS4','BBSR7',70);
# Insert into t1 values('CSQL2', 'LAKS4','BBSR8',80);
# Test the below queries return proper result set or not.
# select * from t1;
# update t1 set f3='Orissa1',f4=100 where f3='BBSR1' and f1='CSQL1';
# update t1 set f3='Orissa1',f4=100 where not(f3='BBSR1') and f1='CSQL2';
# update t1 set f3='Orissa2',f4=200 where f3='BBSR2' or f1='CSQL1';
# update t1 set f3='Orissa3',f4=300 where f1='CSQL1' and f3 like '__issa2';
# update t1 set f3='Orissa4',f4=400 where f2='LAKS2' and f3 like '_r%3';
# update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3','LAKS5');
# update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3',NULL);
# update t1 set f3='Orissa5',f2='LAKS5' where f1='CSQL1' and f3 like 'O_is_a4';
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_logical_upd.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_logical_upd.sql 
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
