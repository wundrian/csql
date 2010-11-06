#!/bin/ksh
# Testing Durability in MMAP architectur
# set DURABILITY = true and MMAP=true in csql.conf
# Start csqlserver.
# Then create a table t1 in CSQL Client.
# Create index idx1 on t1(f1);
# Create the same index idx1 on t1(f1);
# kill the currently running Server.
# Restart the server.
# csqldump should dump the database with table and index information
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
echo DURABILITY=true >>/tmp/csql.conf
echo MMAP=true >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "CREATE TABLE laks(f1 int);" >${REL_PATH}/create.sql
echo "DROP TABLE laks;" >${REL_PATH}/drop.sql

echo "CREATE TABLE laks(f1 int);"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.sql
 exit 1;
fi

echo "CREATE INDEX idx1 on laks(f1);" >${REL_PATH}/indexcreate.sql
echo "CREATE INDEX idx1 ON laks(f1);"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/indexcreate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.isql
   rm -f ${REL_PATH}/indexcreate.sql
 exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/indexcreate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.isql
   rm -f ${REL_PATH}/indexcreate.sql
 exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >${REL_PATH}/before.sql

kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"
echo ""
echo DURABILITY=true >>/tmp/csql.conf
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
if [ $? -ne 0 ]
 then
   echo "Server could not be Started"
   rm -rf /tmp/csql/db
   mkdir -p /tmp/csql/db
   kill -9 $pid
   ipcrm -M 4444 
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/indexcreate.sql
 exit 4;
fi
pid=$!
echo "Server Started"
sleep 2

$CSQL_INSTALL_ROOT/bin/csqldump >${REL_PATH}/after.sql
echo ""
diff ${REL_PATH}/before.sql ${REL_PATH}/after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

rm -f ${REL_PATH}/create.sql
rm -f ${REL_PATH}/drop.sql
rm -f ${REL_PATH}/before.sql ${REL_PATH}/after.sql
rm -f ${REL_PATH}/indexcreate.sql
kill -9 $pid
ipcrm -M 4444
exit 0;
