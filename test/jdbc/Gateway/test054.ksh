#!/bin/ksh
# Connect with connectstring "jdbc:gateway"
# select tuple with WHERE clause having param for some fields(SELECT * FROM t1 WHERE f1=?AND f2=? AND f3=?)
# when csqlserver is not runnig
# GwTest14.java 
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
#export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo "CREATE TABLE t1 (f1 integer, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);" >${REL_PATH}/t1create.sql
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/t1create.sql
   exit 1;
fi
java GwTest14
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "drop table t1;">${REL_PATH}/dp.sql
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

exit 0;
