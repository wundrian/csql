#!/bin/sh
# Autocommit Checking
# Run this test only under csql/test or on this directory.
# Otherwise, it may fail
# set DURABILITY to true in csql.conf
# Start csqlserver. Then create a table in CSQL Client.Insert 5 Records. 
# make Set autocommit off. insert another 5 records and Rollback.
# Kill the Server. 
# Again Restart the Server by setting DURABILITY=true .
# select should Display 1st 5 records.
# 

CSQL_CONF=${PWD}/tools/Durability/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/Durability
fi

rm -f /tmp/csql.conf
rm -rf /tmp/csql/db
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo "DURABILITY=true" >>/tmp/csql.conf
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
   ipcrm -M 4444 -M 6666
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
   ipcrm -M 4444 -M 6666
 exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"

echo ""
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
rm -f ${REL_PATH}/select_t2.sql
rm -f ${REL_PATH}/drop_t2.sql
rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
