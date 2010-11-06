#!/bin/ksh
# set DURABILITY=true and MMAP=false in csql.conf 
# Start csqlserver.Server should be started without any error.
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
echo DURABILITY=true >>/tmp/csql.conf
echo MMAP=false >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = FALSE"
echo "MMAP=false"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
if [ $? -ne 0 ]
 then
  exit 1;
fi

echo "SERVER Started"
echo "Test Passed"
sleep 2
pid=$!
kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
