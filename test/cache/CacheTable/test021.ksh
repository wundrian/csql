#!/bin/ksh
# Test Case

# Create table t4 with f1 int and f2 char,composite primary key (f1,f2) in target database
# Cache it with cachetable tool.
# Check the catalog table whether primary key is composite
# Insert some records which violate composite key
# Insertion should fail
# Unload the table. It should succeed.

input=${PWD}/cache/CacheTable/create.sql
REL_PATH=.
if [ -s "$input" ]
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
if [ $DSN = "db2" ]
then
    isql $DS < ${REL_PATH}/create1db2.sql >/dev/null 2>&1
else
    isql $DS < ${REL_PATH}/create1.sql >/dev/null 2>&1
fi
if [ $? -ne 0 ]
then
    exit 1;
fi
echo table t4 is created with records in target db
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "1 t4 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
then
    isql $DS < ${REL_PATH}/drop1.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 2
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
    isql $DS < ${REL_PATH}/drop1.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 3
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert1.sql

if [ $? -ne 0 ]
then
    isql $DS < ${REL_PATH}/drop1.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 4
fi

$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t4 -u 
isql $DS < ${REL_PATH}/drop1.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0;

