#!/bin/ksh

#  Load table t1 from MySQL using csql -g enter the following command 
#  create index idx on t1 (f1),Index should be created only in csql and not in mysql   

# Run this test only under csql/test or on this directory.
# Otherwise, it may fail
CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/csqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/DDL
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


echo "create table t1(f1 int,f2 int,f3 char(10));">$REL_PATH/t1.sql
isql $DS < $REL_PATH/t1.sql >/dev/null
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    echo "unable to create in target db"
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    rm -f $REL_PATH/t1.sql
    exit 1
fi

rm   /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then
    echo "unable to cache table from target db"
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql
    exit 2 
fi
echo "create index ind1 on t1(f2);">$REL_PATH/cre.sql
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/cre.sql
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
    echo "unable to Unload the table"
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
    rm -f $REL_PATH/t1.sql
    rm -f $REL_PATH/cre.sql
    kill -9 $pid
    ipcrm -M 1199 -M 2277 -M 1947
    exit 3
fi
echo "desc t1;">$REL_PATH/a.sql
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
if [ $? -ne 0 ]
then
    echo "unable to Unload the table"
    isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    rm -f $REL_PATH/t1.sql
    rm -f $REL_PATH/cre.sql
    rm -f $REL_PATH/a.sql
    kill -9 $pid
    ipcrm -M 1199 -M 2277 -M 1947
    exit 4 
fi
isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277 -M 1947
rm   /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
rm -f $REL_PATH/t1.sql
rm -f $REL_PATH/cre.sql
rm -f $REL_PATH/a.sql
exit 0
