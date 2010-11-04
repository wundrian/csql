#!/bin/ksh
#Test case
#16. create table t1,t2 in target DB with 10 records.
#    load t1 table with condition option
#    load t2 table with condition .

#    unload the two tables t1,t2 with -u option.

#  AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
# create table t1,t2 in target DB.
isql $DS < ${REL_PATH}/create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "cachetable -t t1"
echo "cachetable -t t2 -c \"t2f1<5\" " 

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 >/dev/null 2>&1
if [ $? -ne 0 ]
then
    isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf

    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 2;
fi

echo "Table t1 unloaded from CSQL"

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -c "t2f1<5" >/dev/null 2>&1
if [ $? -ne 0 ]
then
     rm -f /tmp/csql/csqltable.conf
     touch /tmp/csql/csqltable.conf   
    
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
    isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 3;
fi

# unload the two tables from csql and remove entry from csqltable.conf

echo "Table t2 unloaded from CSQl"
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1
if [ $? -ne 0 ] 
then
     rm -f /tmp/csql/csqltable.conf
     touch /tmp/csql/csqltable.conf
 
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
     isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1

    cp /tmp/csql.conf $CSQL_CONFIG_FILE
     exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cachetable -t t2 -u >/dev/null 2>&1
if [ $? -ne 0 ]
then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql >/dev/null 2>&1
     isql $DS < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
     rm -f /tmp/csql/csqltable.conf

    cp /tmp/csql.conf $CSQL_CONFIG_FILE
     exit 5;
fi
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DS <${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
    cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

           
