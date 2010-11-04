#!/bin/ksh
#This test requires kernel.shmmax to be 1GB, otherwise it may fail
#

# Start TDB and create 100 tables in TDB t1(f1 int primary key, f2 int), i
#   t2(f1 int primary key, f2 int), ... t100 and insert 10 records each.
# Add entries for all 100 tables in csqltable.conf. 
# Recover with csqlserver -c option. 
# Verify that it recovers all the tables with index information and all 
#   the records using the csqldump tool.

CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/create.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
   REL_PATH=${PWD}/cache/Recovery
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < $REL_PATH/create.sql  >/dev/null 2>&1 
if [ $? -ne 0 ]
then
   exit 2;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
a=1

while [[ $a -lt 101 ]];do
     echo "1 t$a NULL NULL NULL $DSN"
     (( a +=1 ))
done >> /tmp/csql/csqltable.conf 

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 60
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
     kill -9 $pid > /dev/null 2>&1
     ipcrm -M 1199 -M 2277
     isql $DS < $REL_PATH/dropall.sql > /dev/null 2>&1
     exit 3;
fi

isql $DS < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
kill -9 $pid > /dev/null 2>&1
ipcrm -M 1199 -M 2277
exit 0;
