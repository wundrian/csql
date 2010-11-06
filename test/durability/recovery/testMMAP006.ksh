#!/bin/ksh
# Testing Durability in MMAP architecture
# Autocommit Checking
# set DURABILITY=true and MMAP=true in csql.conf
# Start csqlserver. Then create a table in CSQL Client.Insert 5 Records.
# make Set autocommit off. insert another 5 records and Rollback.
# Kill the Server.
# Again Restart the Server by setting DURABILITY=true .
# select should Display 1st 5 records.
#
CSQL_CONF=${PWD}/durability/recovery/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/durability/recovery
fi

rm -f /tmp/csql.conf
rm -f /tmp/csql/db/*
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo "DURABILITY=true" >>/tmp/csql.conf
echo "MMAP=true" >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf


echo "SELECT * FROM t2;" >${REL_PATH}/select_t2.sql
echo "drop table t2;" >${REL_PATH}/drop_t2.sql

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2
echo "CREATING TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t2.sql
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/select_t2.sql
   rm -f ${REL_PATH}/drop_t2.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 1;
fi

echo "INSERTING INTO TABLE"
echo "DEFAULT AUTOCOMMIT MODE ON"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/ins_rollback.sql
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
   rm -f ${REL_PATH}/select_t2.sql
   rm -f ${REL_PATH}/drop_t2.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >>/dev/null 2>&1
if [ $? -eq 0 ]
     then
       echo Durability Works Fine
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
rm -f ${REL_PATH}/select_t2.sql
rm -f ${REL_PATH}/drop_t2.sql
rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 
exit 0;
