#!/bin/ksh
# Statement Caching test with now in timestamp field
# create a table say t1(f1 int, f2 timestamp)
# insert a record say (1,'now')
# select count(*) from t1 where f2 < 'now'; This should display 1
# insert a record say (2,'now')
# select count(*) from t1 where f2 < 'now'; This should display 2
CREATEFILE=${PWD}/sql/StmtCache/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/StmtCache
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

echo "echo create table t1(f1 int, f2 timestamp);" >${REL_PATH}/stmtcache1.sql
echo "create table t1(f1 int, f2 timestamp);" >>${REL_PATH}/stmtcache1.sql
echo "echo insert into t1 values(1,'now');" >>${REL_PATH}/stmtcache1.sql
echo "insert into t1 values(1,'now');" >>${REL_PATH}/stmtcache1.sql

echo "echo select count(*) from t1 where f2 < 'now';" >${REL_PATH}/stmtcache2.sql
echo "select count(*) from t1 where f2 < 'now';" >>${REL_PATH}/stmtcache2.sql

echo "echo insert into t1 values(2,'now');" >${REL_PATH}/stmtcache3.sql
echo "insert into t1 values(2,'now');" >>${REL_PATH}/stmtcache3.sql

echo "echo select count(*) from t1 where f2 < 'now';" >${REL_PATH}/stmtcache4.sql
echo "select count(*) from t1 where f2 < 'now';" >>${REL_PATH}/stmtcache4.sql

sleep 1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache1.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache1.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/stmtcache1.sql ${REL_PATH}/stmtcache2.sql ${REL_PATH}/stmtcache3.sql ${REL_PATH}/stmtcache4.sql
       exit 1;
    fi
fi
sleep 1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache2.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache2.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql 
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/stmtcache1.sql ${REL_PATH}/stmtcache2.sql ${REL_PATH}/stmtcache3.sql ${REL_PATH}/stmtcache4.sql
       exit 1;
    fi
fi
sleep 1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache3.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache3.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/stmtcache1.sql ${REL_PATH}/stmtcache2.sql ${REL_PATH}/stmtcache3.sql ${REL_PATH}/stmtcache4.sql
       exit 3;
    fi
fi

sleep 1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache4.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/stmtcache4.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/stmtcache1.sql ${REL_PATH}/stmtcache2.sql ${REL_PATH}/stmtcache3.sql ${REL_PATH}/stmtcache4.sql
       exit 4;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 5;
fi

rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/stmtcache1.sql ${REL_PATH}/stmtcache2.sql ${REL_PATH}/stmtcache3.sql ${REL_PATH}/stmtcache4.sql
exit 0;
