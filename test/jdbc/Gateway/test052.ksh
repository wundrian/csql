#!/bin/ksh
# Connect with connectstring "jdbc:gateway"
# Open a connection and then close it. After that execute INSERT/QUERY/UPDATE statement. It should fail,when csqlserver is not runnig
# GwTest12.java
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
echo "create table t1 (f1 int,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql
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
java GwTest12
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "drop table t1;">${REL_PATH}/dp.sql
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

exit 0;
