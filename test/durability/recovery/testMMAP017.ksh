#!/bin/ksh
# Testing Durability in MMAP Architecture
# set DURABILITY to true and MMAP=true in csql.conf
# Start csqlserver. Then create a table t1 in CSQL Client. 
# kill the currently running Server. 
# Again Restart the Server by setting DURABILITY=true and Open CSQL Client.
# Create another table t2 .
# Kill the server.
# Continue The same for 20 times. Each time tables should be durable
# All should work Fine
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
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo "DURABILITY=true" >>/tmp/csql.conf
echo "MMAP=true" >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
i=1
while [[ $i -lt 21 ]];do
  echo "CREATING TABLE t$i"
  echo "CREATE TABLE t$i(f1 int,f2 char(100));" >${REL_PATH}/cre_t$i.sql
  $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/cre_t$i.sql >/dev/null 2>&1
  if [ $? -ne 0 ]
   then
     rm -f ${REL_PATH}/cre_t$i.sql
     kill -9 $pid
     ipcrm -M 4444 
   exit 1;
  fi
  
  $CSQL_INSTALL_ROOT/bin/csqldump >before.sql

  kill -9 $pid
  ipcrm -M 4444 
  echo "Server Killed"

  $CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
  pid=$!
  echo "Server Started"
  sleep 2
  $CSQL_INSTALL_ROOT/bin/csqldump >after.sql
  diff before.sql after.sql
  if [ $? -eq 0 ]
     then
         echo Durability Works Fine
  fi
 (( i +=1 ))
done

rm -f before.sql after.sql
i=1
while [[ $i -lt 21 ]];do
 echo "DROP TABLE t$i;" >>${REL_PATH}/dropall.sql
 rm -f cre_t$i.sql 
 (( i +=1 ))
done
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropall.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dropall.sql
kill -9 $pid
ipcrm -M 4444 
exit 0;
