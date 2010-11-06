#!/bin/ksh
# Testing Durability in MMAP Architecture
# set DURABILITY to true and MMAP=true in csql.conf
# Start csqlserver. Then create a table t1 with record size 20. 
# kill the currently running Server. 
# Again Restart the Server by setting DURABILITY=true and MMAP=true 
# Insert 1k records .
# Kill the server.
# Continue The same for 10 times. Each time table with records should be durable
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
echo "CREATE TABLE t1(f1 int,f2 char(15));"
echo "CREATE TABLE t1(f1 int,f2 char(15));" >${REL_PATH}/cre_t1.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/cre_t1.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/cre_t1.sql
   rm -f ${REL_PATH}/ins_1000.sql 
   kill -9 $pid
   ipcrm -M 4444 
 exit 1;
fi     

echo "SELECT COUNT(*) FROM t1;" >${REL_PATH}/sel.sql
i=1
while [[ $i -lt 11 ]];do
  j=1
  while [[ $j -lt 1001 ]];do
    echo "INSERT INTO t1 VALUES($i$j,'CSQL$i$j');" >>${REL_PATH}/ins_1000.sql
    (( j +=1 ))
  done    
  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/ins_1000.sql >/dev/null 2>&1
  if [ $? -ne 0 ]
   then
     rm -f ${REL_PATH}/cre_t1.sql
     rm -f ${REL_PATH}/ins_1000.sql 
     kill -9 $pid
     ipcrm -M 4444 
   exit 1;
  fi     
  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sel.sql
  rm -f ${REL_PATH}/ins_1000.sql
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
rm -f before.sql after.sql
done

echo "DROP TABLE t1;" >drp.sql
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/drp.sql
rm -f ${REL_PATH}/cre_t1.sql
rm -f ${REL_PATH}/sel.sql 
kill -9 $pid
ipcrm -M 4444 
exit 0;
