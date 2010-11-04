#!/bin/ksh
# Test Case
# 6. Create table t1 in mysql with primary key. Insert 10 rows. 
#    Cache the table in csql.
#    Run $ cacheverify -t t1 
#         The output should display the number of records present in csql 
#         and mysql separately.
#    Run $ cacheverify -t t1 -p 
#         The output should display no missing records in either database.
#    Run $ cacheverify -t t1 -f
#         The output should display no missing records and should display 
#                               the data is consistent in both databases.


#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/mysqlinput.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
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
    isql $DS  < ${REL_PATH}/oracleinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
elif [ $DSN = "myodbc3" ]
then
    isql $DS < ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
elif [ $DSN = "sybase" ]
then
    isql $DS < ${REL_PATH}/sybaseinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
elif [ $DSN = "db2" ]
then
    isql $DS < ${REL_PATH}/db2input.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
else
    isql $DS < ${REL_PATH}/psqlinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
        exit 1;
    fi
    
fi
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf


$CSQL_INSTALL_ROOT/bin/cachetable -t t1
if [ $? -ne 0 ]
then
    exit 2;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    exit 5;
fi

exit 0;
