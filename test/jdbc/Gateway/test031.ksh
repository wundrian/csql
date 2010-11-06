#!/bin/ksh
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

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "create table t1 (f1 int NOT NULL,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql
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
java GwStmt1 
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
