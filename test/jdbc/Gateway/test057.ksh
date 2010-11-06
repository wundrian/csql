#!/bin/ksh
# Call procedure from csql Gateway
# Currently it works for mysql and oracle
# Procedure01.java

#Author:= Bijaya

TESTFILE=${PWD}/jdbc/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
if [ "$DSN" = "myodbc3" ]
then
    echo "create table t1(f1 int,f2 int);" >${REL_PATH}/t1create.sql
    echo "create procedure InParamSelect(in p1 int) select * from t1 where f1<p1;" > ${REL_PATH}/proc.sql
    echo "drop procedure InParamSelect;">>${REL_PATH}/t1create.sql
    echo "drop  procedure InParamSelect;" >>${REL_PATH}/dp.sql
elif [ "$DSN" = "oracle" ]
then
    echo "create table t1(f1 number(9),f2 number(9));" >${REL_PATH}/t1create.sql
    echo "CREATE or replace PACKAGE CsqlRef AS TYPE ename_cur IS REF CURSOR; PROCEDURE InParamSelect(Ename IN OUT ename_cur, p1 IN NUMBER); END;">${REL_PATH}/proc.sql
    echo "CREATE or replace PACKAGE BODY CsqlRef AS PROCEDURE InParamSelect(Ename IN OUT ename_cur, p1 IN NUMBER) AS  BEGIN  OPEN Ename for SELECT * from t1 where f1 < p1; END; END;">>${REL_PATH}/proc.sql
    echo "drop PACKAGE CsqlRef;" >>${REL_PATH}/dp.sql
fi
echo "insert into t1 values(12,23);">>${REL_PATH}/t1create.sql
echo "insert into t1 values(13,24);">>${REL_PATH}/t1create.sql
echo "insert into t1 values(14,25);">>${REL_PATH}/t1create.sql
echo "insert into t1 values(15,26);">>${REL_PATH}/t1create.sql
echo "drop table t1;">${REL_PATH}/dp.sql
#echo $DS
isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   rm -f ${REL_PATH}/proc.sql
   exit 2;
fi
isql $DS < ${REL_PATH}/proc.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   rm -f ${REL_PATH}/proc.sql
   exit 3;
fi

java Procedure01
if [ $? -ne 0 ]
then
   exit 2;
fi

isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql
rm -f ${REL_PATH}/proc.sql
exit 0;
