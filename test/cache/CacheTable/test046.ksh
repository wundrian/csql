#!/bin/ksh
# Test Case
# Create table t1 in Target DB with 3 fields say (f1 int, f2 smallint, f3 int). 
# Create composite index on f1 and f3 field. 
# Set CACHE_TABLE=true in csql.conf
# Cache the table t1
# She Catalog tool displays the composite key index informations or not
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
echo "CREATE TABLE t1(f1 int, f2 smallint, f3 int);" >${REL_PATH}/t1create_compo.sql
echo "CREATE INDEX idx1 on t1(f1,f3)" >>${REL_PATH}/t1create_compo.sql

isql $DS < ${REL_PATH}/t1create_compo.sql
if [ $? -ne 0 ]
 then
 rm -f ${REL_PATH}/t1create_compo.sql
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

$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
 then
 rm -f ${REL_PATH}/t1create_compo.sql
 isql $DS < ${REL_PATH}/drop_t1.sql
 ipcrm -M 2288 -M 3377 
 exit 2;
fi

$CSQL_INSTALL_ROOT/bin/catalog -l
if [ $? -ne 0 ]
 then
 $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
 rm -f ${REL_PATH}/t1create_compo.sql
 isql $DS < ${REL_PATH}/drop_t1.sql
 ipcrm -M 2288 -M 3377 
 exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
if [ $? -ne 0 ]
 then
 rm -f ${REL_PATH}/t1create_compo.sql
 isql $DS < ${REL_PATH}/drop_t1.sql
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
