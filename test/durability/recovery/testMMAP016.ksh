#!/bin/ksh
# Testing Durability in MMAP Architecture.
# set DURABILITY=true and MMAP=true in csql.conf
# Start csqlserver. 
# Then create a table t1 in CSQL Client.
# Set MAX_SYS_DB_SIZE=10MB and MAX_DB_SIZE=100MB 
# Create a table say t1 having 10k record with no index.
# Create a table say t1 having 10k record with UNIQUE HASH Index.
# Create a table say t1 having 10k record with UNIQUE TREE Index.
# Create a table say t1 having 10k record with PRIMARY KEY on INT field.
# Create a table say t1 having 10k record with PRIMARY KEY on CHAR field.
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

i=1
while [[ $i -lt 6 ]];do
 j=1
 while [[ $j -lt 2001 ]];do
  echo "INSERT INTO t$i VALUES($j,'LAKSHYA_CSQL$j');"
  (( j +=1 ))
 done >>${REL_PATH}/ins_t$i.sql
 (( i +=1 ))
done

i=1
while [[ $i -lt 6 ]];do
 echo "DROP TABLE t$i;"
 (( i +=1 ))
done >>${REL_PATH}/drop_5table.sql

rm -f /tmp/csql.conf
rm -rf /tmp/csql/db
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=5555 >>/tmp/csql.conf
echo USER_DB_KEY=7777 >>/tmp/csql.conf
echo MAX_SYS_DB_SIZE=10485760 >>/tmp/csql.conf
echo MAX_DB_SIZE=104857600 >>/tmp/csql.conf
echo DURABILITY=true >>/tmp/csql.conf
echo MMAP=true >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 3

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_5teble.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   i=1
   while [[ $i -lt 6 ]];do
    rm -f ${REL_PATH}/ins_t$i.sql
    (( i +=1 ))
   done
   rm -f ${REL_PATH}/drop_5table.sql
   kill -9 $pid
   ipcrm -M 5555 
 exit 1;
fi

i=1
while [[ $i -lt 6 ]];do
 $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/ins_t$i.sql >/dev/null 2>&1
 (( i +=1 ))
done
if [ $? -ne 0 ]
 then
   i=1
   while [[ $i -lt 6 ]];do
     rm -f ${REL_PATH}/ins_t$i.sql
     (( i+=1 ))
   done
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_5table.sql
   rm -f ${REL_PATH}/drop_5table.sql
   kill -9 $pid
   ipcrm -M 5555 
 exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csqldump >${REL_PATH}/before.sql
sleep 10
kill -9 $pid
ipcrm -M 5555 
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
   i=1
   while [[ $i -lt 6 ]];do
     rm -f ${REL_PATH}/ins_t$i.sql
     (( i +=1 ))
   done

   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_5table.sql
   rm -f ${REL_PATH}/drop_5table.sql
   kill -9 $pid
   ipcrm -M 5555 
 exit 4;
fi
pid=$!
echo "Server Started"
sleep 30

$CSQL_INSTALL_ROOT/bin/csqldump >${REL_PATH}/after.sql
echo ""
sleep 1
diff ${REL_PATH}/before.sql ${REL_PATH}/after.sql
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

i=1
while [[ $i -lt 6 ]];do
  rm -f ${REL_PATH}/ins_t$i.sql
  (( i +=1 ))
done
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_5table.sql
rm -f ${REL_PATH}/drop_5table.sql
kill -9 $pid
ipcrm -M 5555 
exit 0;
