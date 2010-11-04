#!/bin/ksh
# Test Case

# Create table t5 with f1 int unique and f2 int,primary key (f2) in target database
# Cache it with cachetable tool.
# Check with catalog -D chunk tool whether index is created for both primary as well as unique.
# Insert some records in CSQL which violate unique key. It should fail.

input=${PWD}/cache/CacheTable/createt5.sql
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

if [ $DSN = "oracle" ]
then
    isql $DS < ${REL_PATH}/createt5.oracle >/dev/null 2>&1
elif [ $DSN = "db2" ]
then
    isql $DS < ${REL_PATH}/createt5db2.sql >/dev/null 2>&1
else
    isql $DS < ${REL_PATH}/createt5.sql >/dev/null 2>&1
fi
if [ $? -ne 0 ]
then
    exit 1;
fi
echo table t5 is created with records in target db

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver  >/dev/null 2>&1 &
pid=$!
sleep 5
echo "1 t5 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf
echo "1 t6 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R
if [ $? -ne 0 ]
then
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 1;
fi

#$CSQL_INSTALL_ROOT/bin/csqldump

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql > /dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    kill -9 $pid
    ipcrm -M 4000 -M 4500
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql > /dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf
   kill -9 $pid
   ipcrm -M 4000 -M 4500
   exit 3;
fi
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t5 -u
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t6 -u
isql $DS < ${REL_PATH}/drop5.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop5.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
kill -9 $pid
ipcrm -M 4000 -M 4500
exit 0;

