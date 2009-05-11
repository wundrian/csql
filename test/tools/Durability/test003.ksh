#!/bin/sh
# Run this test only under csql/test or on this directory.
# Otherwise, it may fail
# set DURABILITY = true in csql.conf
# Start csqlserver. Then create a table in CSQL Client.
# kill the currently running Server. 
# Restart the server by setting DURABILITY = false. and Open CSQL Client.
# SHOW TABLES; Statement  should not display any table.
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
echo DURABILITY=true >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "CREATE TABLE laks(f1 int);" >${REL_PATH}/create.sql
echo "DROP TABLE laks;" >${REL_PATH}/drop.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 -M 6666
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.sql
 exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"
echo ""
echo DURABILITY=false >>/tmp/csql.conf
echo "Durablity = FALSE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2

$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
echo ""
diff before.sql after.sql

rm -f ${REL_PATH}/create.sql
rm -f ${REL_PATH}/drop.sql
rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
