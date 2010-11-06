#!/bin/ksh
# Checking page size
# Increase PAGE_SIZE 2 times of the default
# Set MAX_SYS_DB_SIZE=10485760
# Set MAX_DB_SIZE=104857600
# check all DDL Operations on bigger tables taking recordsize more than 1k
# DDL (create table,create index,drop table, drop index)
#
CSQL_CONF=${PWD}/tools/Pagesize/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/Pagesize
fi

rm -f /tmp/csql.conf
rm -rf /tmp/csql/db
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo PAGE_SIZE=16384 >>/tmp/csql.conf
echo MAX_SYS_DB_SIZE=10485760 >>/tmp/csql.conf
echo MAX_DB_SIZE=104857600 >>/tmp/csql.conf

export CSQL_CONFIG_FILE=/tmp/csql.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
if [ $? -ne 0 ]
 then
 exit 1;
fi
pid=$!
sleep 2

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_8tab.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 2;
fi

i=1
while [[ $i -lt 2001 ]];do
 echo "INSERT INTO t8 VALUES($i,$i,'CSQL_Lakshya$i');" 
 (( i +=1 ))
done >>${REL_PATH}/insert_t8.sql 

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_t8.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_8tab.sql
   rm -f ${REL_PATH}/insert_t7.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 3;
fi
(( i -=1 ))
echo "$i record inserted"

echo "DELETE FROM t8 WHERE f3!='CSQL_Lakshya';" >>${REL_PATH}/delete_t8.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/delete_t8.sql
if [ $? -ne 0 ]
 then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_8tab.sql
   rm -f ${REL_PATH}/insert_t8.sql
   rm -f ${REL_PATH}/delete_t8.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 4;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_8tab.sql
if [ $? -ne 0 ]
 then
   rm -f ${REL_PATH}/insert_t8.sql
   rm -f ${REL_PATH}/delete_t8.sql
   kill -9 $pid
   ipcrm -M 4444 -M 6666
 exit 5;
fi

kill -9 $pid
ipcrm -M 4444 -M 6666

rm -f ${REL_PATH}/insert_t8.sql
rm -f ${REL_PATH}/delete_t8.sql
exit 0;
