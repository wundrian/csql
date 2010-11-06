#!/bin/ksh
# Testing VARCHAR Datatype without index
# All DML testing
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo create table t1(f1 varchar(20),f2 varchar(30));" >${REL_PATH}/varchar.sql
echo "create table t1(f1 varchar(20),f2 varchar(30));" >>${REL_PATH}/varchar.sql
echo "insert into t1 values('CSQL1','Lakshya1');" >>${REL_PATH}/varchar.sql
echo "insert into t1 values('CSQL2','Lakshya2');" >>${REL_PATH}/varchar.sql
echo "insert into t1 values('CSQL3','Lakshya3');" >>${REL_PATH}/varchar.sql
echo "insert into t1 values('CSQL4','Lakshya4');" >>${REL_PATH}/varchar.sql
echo "insert into t1 values('CSQL5','Lakshya5');" >>${REL_PATH}/varchar.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar.sql
echo "select * from t1;" >>${REL_PATH}/varchar.sql
echo "echo select * from t1 where f1='CSQL4' or f1='CSQL2';" >>${REL_PATH}/varchar.sql
echo "select * from t1 where f1='CSQL4' or f1='CSQL2';" >>${REL_PATH}/varchar.sql
echo "echo update t1 set f2='LAKSHYA' where f1='CSQL2' or f1='CSQL4';" >>${REL_PATH}/varchar.sql
echo "update t1 set f2='LAKSHYA' where f1='CSQL2' or f1='CSQL4';" >>${REL_PATH}/varchar.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar.sql
echo "select * from t1;" >>${REL_PATH}/varchar.sql
echo "echo delete from t1 where f1 in ('CSQL1','CSQL3','CSQL5');" >>${REL_PATH}/varchar.sql
echo "delete from t1 where f1 in ('CSQL1','CSQL3','CSQL5');" >>${REL_PATH}/varchar.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar.sql
echo "select * from t1;" >>${REL_PATH}/varchar.sql

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/varchar.sql ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi
rm -f ${REL_PATH}/varchar.sql ${REL_PATH}/dropt1.sql
exit 0;
