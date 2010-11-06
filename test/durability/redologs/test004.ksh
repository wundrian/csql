#!/bin/ksh
# create table, create primary index, insert, insert duplicate value, 
# drop index, insert duplicate value and check stmt and redo logs with csqldump
#check stmtid start from last stmtid after recover
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

echo "CREATE TABLE laks(f1 int not null, f2 int);" >${REL_PATH}/t1.sql
echo "INSERT INTO laks values (10, 10);" >>${REL_PATH}/t1.sql
echo "create index idx on laks (f1) primary hash;" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (10, 10);" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (50, 50);" >>${REL_PATH}/t1.sql
echo "DROP Index idx;" >>${REL_PATH}/t1.sql
echo "INSERT INTO laks values (50, 50);" >>${REL_PATH}/t1.sql
#echo "DROP table laks;" >>${REL_PATH}/t1.sql

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
$CSQL_INSTALL_ROOT/bin/csqldump


rm -f ${REL_PATH}/t1.sql
kill -9 $pid
ipcrm -M 4444 -M 6666 
exit 0;
