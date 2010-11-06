#!/bin/ksh
TESTFILE=${PWD}/jdbc/network/Adapter/ConTest01.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
	REL_PATH=`pwd`/jdbc/network/Adapter
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

#table creation
echo "create table t1 (f1 int,f2 char(10),primary key(f1));" >${REL_PATH}/t1create.sql

isql $DS < ${REL_PATH}/t1create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f ${REL_PATH}/t1create.sql
    exit 2;
fi

java AdStmt1 
if [ $? -ne 0 ]
then
  exit 3;
fi

echo "drop table t1;">${REL_PATH}/dp.sql
isql $DS < ${REL_PATH}/dp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dp.sql
rm -f ${REL_PATH}/t1create.sql

if [ $? -ne 0 ]
then
   exit 4;
fi
exit 0;
                

