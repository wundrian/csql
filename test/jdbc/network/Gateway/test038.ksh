#!/bin/ksh
#JDBC GATEWAY CACHE 
TESTFILE=${PWD}/jdbc/network/Gateway/ConnTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/network/Gateway
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo "CACHE_TABLE=true" >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
if [ $DSN = "oracle" ]
then
    echo "CREATE TABLE t1 (f1 number(9), f2 number(4), f4 number(37), f5 float, f6 char(10), f7 date, f8 date, f9 timestamp);" >${REL_PATH}/t1create.sql
else
    echo "CREATE TABLE t1 (f1 integer, f2 smallint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);" >${REL_PATH}/t1create.sql
fi
isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
echo "drop table t1;">${REL_PATH}/dp.sql
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
   rm -f ${REL_PATH}/dp.sql
   exit 2;
fi
java GwStmt8
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
   rm -f ${REL_PATH}/dp.sql
   exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
   rm -f ${REL_PATH}/dp.sql
   exit 4;
fi
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql
exit 0;
