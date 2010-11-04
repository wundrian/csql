#!/bin/ksh
# Test Case
#cacheverify test after all Non-select dml (primary key on int field) (cache/CacheVerify/test010.ksh)
#Create table t1 in mysql with primary key on int field. Insert 5 rows.
#Cache the table in csql.
#Run $ cacheverify -t t1. The output should display the number of records present in csql and mysql same.
#Run $ cacheverify -t t1 -p. The output should display no missing records in either database.
#Run $ cacheverify -t t1 -f. The output should display no missing records and should display the data is consistent in both databases.
#Update 2 records in csql using csql -g.
#Run $ cacheverify -t t1 -f
#The output should display no missing records and should display the data is consistent in both databases.
#delete 2 records in csql using csql -g.
#Run $ cacheverify -t t1 -p
#The output should display no missing records in either database.
#Update 2 records in Mysql.
#Run $ cacheverify -t t1 -f.
#The output should display the 4 inconsistent records. Only those fields with different values should be displayed for inconsistent records.
#delete 2 records in Mysql.
#Run $ cacheverify -t t1 -p.
#The output should display the primary key field values for missing records in either of the databases in ascending order.
 
input=${PWD}/cache/CacheVerify/mysqlinput10.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
echo CACHE_TABLE=true>>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
 exit 1;
fi

if [ $DSN = "myodbc3" ]
then
   isql $DS < ${REL_PATH}/mysqlinput11.sql >/dev/null 2>&1
elif [ $DSN = "oracle" ]
then
   isql $DS < ${REL_PATH}/oracleinput11.sql >/dev/null 2>&1
elif [ $DSN = "sybase" ]
then
   isql $DS < ${REL_PATH}/sybaseinput11.sql >/dev/null 2>&1
elif [ $DSN = "db2" ]
then
   isql $DS < ${REL_PATH}/db2input11.sql >/dev/null 2>&1
else
   isql $DS < ${REL_PATH}/psqlinput11.sql >/dev/null 2>&1
fi
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 2;
fi
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

sleep 1

$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 3;
fi

sleep 1
echo cacheverify -t t1
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 4;
fi

echo cacheverify -t t1 -p
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 5;
fi

echo cacheverify -t t1 -f
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 6;
fi

echo updating 2 records in csql through gateway
$CSQL_INSTALL_ROOT/bin/csql -g -s ${REL_PATH}/csqlupd.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 7;
fi

echo cacheverify -t t1 -f
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 8;
fi

echo deleting 2 records in csql through gateway
$CSQL_INSTALL_ROOT/bin/csql -g -s ${REL_PATH}/csqldel.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 9;
fi

echo cacheverify -t t1 -p
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 10;
fi

echo updating 2 records in mysql
isql $DS < ${REL_PATH}/mysqlupd.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 11;
fi

echo cacheverify -t t1 -f
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 12;
fi

echo deleting 2 records in mysql
isql $DS < ${REL_PATH}/mysqldel.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 13;
fi

echo cacheverify -t t1 -p
$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
 $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
 exit 14;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
exit 0;
