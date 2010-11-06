#!/bin/ksh
# Testing Durability in MMAP architecture
# Set MMAP=true in csql.conf
# set DURABILITY to false in csql.conf (Default)
# Start csqlserver. 
# Server should not be started providing error message
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
echo MMAP=true >>/tmp/csql.conf
echo DURABILITY=false >>/tmp/csql.conf

export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "MMAP = true"
echo "DURABILITY = FALSE"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
if [ $? -ne 0 ]
 then
   echo Test Failed
 exit 1;
fi

kill -9 $! 
echo Test Passed
exit 0;
