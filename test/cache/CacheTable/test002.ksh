#!/bin/ksh
# Test Case
# 2. Create table t1 with primary key in mysql. Cache the table in csql.
#    Check for user authentication: 
#    $ cachetable [-U username] [-P password] -t t1 
#         by entering
#    a. correct username correct password - should pass
#    b. correct username wrong password - should return error
#    c. wrong username correct password - should return error
#    d. wrong username wrong password - should return error

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi
cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi
echo $DS
isql $DS < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then   
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# check with correct username and correct password
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P manager -t t1 
if [ $? -ne 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

# correct username and wrong password
$CSQL_INSTALL_ROOT/bin/cachetable -U root -P MANAGER -t t1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

# wrong username and correct password
$CSQL_INSTALL_ROOT/bin/cachetable -U ROOT -P manager -t t1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 4;
fi

#wrong username and wrong password
$CSQL_INSTALL_ROOT/bin/cachetable -U ROOT -P MANAGER -t t1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 5;
fi
 
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
#rm -f /tmp/csql/csqltable.conf
#touch /tmp/csql/csqltable.conf

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

