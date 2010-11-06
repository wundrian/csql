#!/bin/ksh
# Primary key and Foreign Key
# Create table t1 (f1 varchar(10), f2 int, primary key(f1));
# Create table t2 (f1 varchar(10), f2 bigint, foreign key(f1) references t1(f1));
# t1.f1 should not allow NULL Value, Duplicate value.
# Through update statement try to update f1 field of t1. It should be failed due to primary key
# t2.f1 should allow only values which are in t1.f1.
# Delete records from t1 table which has the dependancy in t2 table. It should be failed due to parent child dependancy.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo Create table t1 (f1 varchar(10), f2 int, primary key(f1));" >${REL_PATH}/varchar_pkek_fkey.sql
echo "Create table t1 (f1 varchar(10), f2 int, primary key(f1));" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo Create table t2 (f1 varchar(10), f2 bigint, foreign key(f1) references t1(f1));" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "Create table t2 (f1 varchar(10), f2 bigint, foreign key(f1) references t1(f1));" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t1 values('CSQL1',1);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t1 values('CSQL2',2);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo insert into t1 values(NULL,3);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t1 values(NULL,3);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo insert into t1 values('CSQL2',4);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t1 values('CSQL2',4);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo update t1 set f1='CSQL1' where f1='CSQL2';" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "update t1 set f1='CSQL1' where f1='CSQL2';" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t2 values('CSQL1',10);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t2 values('CSQL2',20);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo insert into t2 values('CSQL3',30);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "insert into t2 values('CSQL3',30);" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo select * from t2;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "select * from t2;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo delete from t1 where f1='CSQL1';" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "delete from t1 where f1='CSQL1';" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "select * from t1;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "echo select * from t2;" >>${REL_PATH}/varchar_pkek_fkey.sql
echo "select * from t2;" >>${REL_PATH}/varchar_pkek_fkey.sql

echo "drop table t2;" >${REL_PATH}/drop.sql
echo "drop table t1;" >>${REL_PATH}/drop.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_pkek_fkey.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_pkek_fkey.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql
       rm -f ${REL_PATH}/varchar_pkek_fkey.sql ${REL_PATH}/drop.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/varchar_pkek_fkey.sql ${REL_PATH}/drop.sql
exit 0;
