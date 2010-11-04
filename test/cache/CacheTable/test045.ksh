#!/bin/ksh
# Test Case
# Create table t1 in Target DB and insert 1 records in TDB. 
# Set CACHE_TABLE=true in csql.conf
# Create a table t1 with same schema as TDB at CSQL.
# DML happen in CSQL, Should not propagate to target Database
#
CSQL_CONF=${PWD}/cache/CacheTable/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/CacheTable
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

# Site1 Configuration
mkdir -p /tmp/CSQL
mkdir -p /tmp/CSQL/log
mkdir -p /tmp/CSQL/log/csql
mkdir -p /tmp/CSQL
mkdir -p /tmp/CSQL/db
cp /tmp/csql.conf /tmp/CSQL/
echo SYS_DB_KEY=2288 >>/tmp/CSQL/csql.conf
echo USER_DB_KEY=3377 >>/tmp/CSQL/csql.conf
echo LOG_FILE=/tmp/CSQL/log/csql/log.out >>/tmp/CSQL/csql.conf
echo DATABASE_FILE=/tmp/CSQL/db >>/tmp/CSQL/csql.conf
echo CACHE_TABLE=true >>/tmp/CSQL/csql.conf
echo SITE_ID=1 >>/tmp/CSQL/csql.conf
echo TABLE_CONFIG_FILE=/tmp/CSQL/csqltable.conf >>/tmp/CSQL/csql.conf
sleep 2
echo CREATING TABLE t1 and INSERTING 1 RECORDS IN TARGET DB
if [ "$DSN" = "sybase" ]
then
    isql $DS < ${REL_PATH}/cre_ins_sybase.sql
else
    isql $DS < ${REL_PATH}/cre_ins_tdb.sql 
fi
if [ $? -ne 0 ]
 then
 isql $DS < ${REL_PATH}/drop_t1.sql
 exit 1;
fi

# Setup Environment For CSQL
export CSQL_CONFIG_FILE=/tmp/CSQL/csql.conf
rm -f /tmp/CSQL/csqltable.conf  
touch /tmp/CSQL/csqltable.conf  

# RUN CSQL SERVER at CSQL
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid1=$!
sleep 2

#Insertion at CSQL
echo CREATING TABLE t1 and INSERTING 1 RECORDS AT CSQL
$CSQL_INSTALL_ROOT/bin/csql -g -u root -p manager -s ${REL_PATH}/cre_ins_csql.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid1 
   ipcrm -M 2288 -M 3377 
   isql $DS < ${REL_PATH}/drop_t1.sql
 exit 2;
fi

echo "AFTER INSERT AT CSQL DATA IN TDB"
isql $DS < ${REL_PATH}/select_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid1
   ipcrm -M 2288 -M 3377 
   isql $DS < ${REL_PATH}/drop_t1.sql
 exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_t1.sql
if [ $? -ne 0 ]
then
   kill -9 $pid1
   ipcrm -M 2288 -M 3377
   exit 4;
fi

isql $DS < ${REL_PATH}/drop_t1.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid1
   ipcrm -M 2288 -M 3377 
 exit 5;
fi

rm -rf /tmp/CSQL
kill -9 $pid1
ipcrm -M 2288 -M 3377
exit 0;
