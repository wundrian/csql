#!/bin/ksh
#Insert 5 stmt, upd 2 stmt, del 1 stmt, select 2 record
# check stmt and redo logs. Recover and check logs
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

echo "CREATE TABLE laks(f1 int, f2 int);" >${REL_PATH}/t1.sql
echo "INSERT INTO laks values (10, 10);" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (20, 20);" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (30, 30);" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (40, 40);" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (50, 50);" >>${REL_PATH}/t1.sql
echo "UPDATE laks set f2=60 where f1=30;" >>${REL_PATH}/t1.sql
echo "UPDATE laks set f2=70 where f1=30;" >>${REL_PATH}/t1.sql
echo "DELETE FROM laks where f1=20;" >>${REL_PATH}/t1.sql
echo "SELECT * FROM laks where f1 > 30;" >>${REL_PATH}/t1.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/t1.sql
if [ $? -ne 0 ]
then
  kill -9 $pid
  ipcrm -M 4444 -M 6666
  rm -f ${REL_PATH}/t1.sql
exit 1;
fi
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

rm -f ${REL_PATH}/t1.sql
kill -9 $pid
ipcrm -M 4444 -M 6666 
exit 0;
