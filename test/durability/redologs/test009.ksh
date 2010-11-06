#!/bin/ksh
#prepare param stmt, set param and do not execute, 
#check stmt and redo logs, recover, check stmt and redo logs contain nothing
#
CSQL_CONF=${PWD}/durability/redologs/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/durability/redologs
fi

rm -f /tmp/csql.conf
rm -rf /tmp/csql/db/*
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo ID_SHM_KEY=6666 >>/tmp/csql.conf
echo DURABILITY=true >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "CREATE TABLE t1(f1 int not null, f2 int not null);" >${REL_PATH}/t1.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/t1.sql
if [ $? -ne 0 ]
then
  kill -9 $pid
  ipcrm -M 4444 -M 6666
  rm -f ${REL_PATH}/t1.sql
exit 1;
fi
$REL_PATH/stmtTest9
$CSQL_INSTALL_ROOT/bin/redo -al

kill -9 $pid
ipcrm -M 4444 -M 6666 
echo "Server Killed"
echo ""
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2

$CSQL_INSTALL_ROOT/bin/redo -al
$CSQL_INSTALL_ROOT/bin/csqldump


rm -f ${REL_PATH}/t1.sql
kill -9 $pid
ipcrm -M 4444 -M 6666 
exit 0;
