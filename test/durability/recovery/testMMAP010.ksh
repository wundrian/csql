#!/bin/ksh
# Testing Durability in MMAP architecture
# Unique Index test
# Testing All the operation in CSQl ((After Each Operation Kill the server and Restart the server again for Another Operation)
# set DURABILITY=true and MMAP=true in csql.conf
# Start csqlserver. Then create a table in CSQL Client.Insert 5 Records.
# kill the currently running Server.
# Again Restart the Server by setting DURABILITY=true and Open CSQL Client.
# Continue The same For All Operations in CSQL.
# All should work Fine
#

CSQL_CONF=${PWD}/durability/recovery/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/durability/recovery
fi

rm -f /tmp/csql.conf
rm -rf /tmp/csql/db
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo "DURABILITY=true" >>/tmp/csql.conf
echo "MMAP=true" >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2
echo "CREATING TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_10.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
 exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo count=1
echo "Durablity = TRUE"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Checking Durability"
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

echo "INSERTING INTO TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/index_10.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo count=2
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

echo "INSERTING INTO TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_10.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo count=3
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

echo "UPDATING RECORDS IN TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/update_10.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 5;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo count=4
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

echo "DELETING RECORDS FROM TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/delete_10.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 7;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo count=5
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

echo "DROPPING TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
 exit 9;
fi

rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 
exit 0;
