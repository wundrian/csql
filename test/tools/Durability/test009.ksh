#!/bin/sh
# Set DURABILITY to true in csql.conf
# Start csqlserver. in CSQl client create a table and insert 5 recored
# 50 times kill and start the server
# Restart csqlserver again. 
# Select Should fetch those inserted 5 records
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


echo "drop table t2;" >${REL_PATH}/drop_t2.sql

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 1
echo "CREATING TABLE"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t2.sql
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/drop_t2.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 1;
fi

echo "INSERTING INTO TABLE"
echo "DEFAULT AUTOCOMMIT MODE ON"
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_a.sql
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
   rm -f ${REL_PATH}/drop_t2.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"

for((i=1;i<=50;i++))
do
    echo count=$i
    $CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
    pid=$!
    echo "Server Started"  
    sleep 2
    echo "Checking Durability"
    $CSQL_INSTALL_ROOT/bin/csqldump >after.sql
    diff before.sql after.sql
    if [ $? -eq 0 ]
     then
       echo Durability Works Fine
    fi

    echo "INSERTING INTO TABLE"
    echo "DEFAULT AUTOCOMMIT MODE ON"
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_a.sql
    if [ $? -ne 0 ]
     then
       $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
       rm -f ${REL_PATH}/drop_t2.sql
       kill -9 $pid
       ipcrm -M 4444 -M 6666
     exit 2;
    fi

    $CSQL_INSTALL_ROOT/bin/csqldump >before.sql
    kill -9 $pid
    ipcrm -M 4444 -M 6666
    echo "Server Killed"
done

echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 1
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
 then
   echo Durability Works Fine
fi
echo "SELECT * FROM t2;" >${REL_PATH}/select_t2.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_t2.sql
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
   rm -f ${REL_PATH}/drop_t2.sql
   rm -f ${REL_PATH}/select_t2.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_t2.sql
rm -f ${REL_PATH}/drop_t2.sql
rm -f ${REL_PATH}/select_t2.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"
exit 0;
