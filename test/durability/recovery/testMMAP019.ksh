#!/bin/ksh
# Testing Durability in MMAP Architecture
# set DURABILITY to true and MMAP=true in csql.conf
# Start csqlserver. 
# Then create a table t1 with record size 20. 
# Insert 1k Records
# kill the currently running Server. 
# set DURABILITY to true and MMAP=true in csql.conf
# Start csqlserver. 
# Insert another 1k Records. 
# All inserted records should be durable
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

echo "DURABILITY=true and MMAP=true"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2

echo "SELECT COUNT(*) from t1;" >${REL_PATH}/sel.sql
echo "CREATE TABLE t1(f1 int,f2 char(15));"
echo "CREATE TABLE t1(f1 int,f2 char(15));" >${REL_PATH}/cre_t1.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/cre_t1.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/cre_t1.sql
   kill -9 $pid
   ipcrm -M 4444 
 exit 1;
fi     
j=1
while [[ $j -lt 1001 ]];do
  echo "INSERT INTO t1 VALUES($j,'CSQL$j');" >>${REL_PATH}/ins_1000.sql
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
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sel.sql
       echo Durability Works Fine
fi
rm -f before.sql after.sql
echo "I-Pass Test over"

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql
kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"

echo "DURABILITY=true and MMAP=true"

echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo "DURABILITY=true" >>/tmp/csql.conf
echo "MMAP=true" >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
diff before.sql after.sql
if [ $? -eq 0 ]
   then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sel.sql
       echo Durability Works Fine
fi
rm -f before.sql after.sql
echo "II-Pass Test over"


$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/ins_1000.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/cre_t1.sql
   rm -f ${REL_PATH}/ins_1000.sql 
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
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/sel.sql
       echo Durability Works Fine
fi
rm -f before.sql after.sql
echo "III-Pass Test over"

echo "DROP TABLE t1;" >drp.sql
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drp.sql >/dev/null 2>&1
rm -f ${REL_PATH}/drp.sql
rm -f ${REL_PATH}/sel.sql
rm -f ${REL_PATH}/cre_t1.sql
rm -f ${REL_PATH}/ins_1000.sql
kill -9 $pid
ipcrm -M 4444 
exit 0;
