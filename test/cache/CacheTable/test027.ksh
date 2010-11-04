#!/bin/ksh
#Test case 27.
#  create t1 table with some records in target DB.
#  cache it with -c and -f option
#  Insert some records which satisfy the cache condition
#  Insert some records which do not satisfy the cache condition
#  Reload table with -r option
#  It should get all records which satisfy the condition for specified fields

#  AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
 then
 REL_PATH=${PWD}/cache/CacheTable
fi
rm -f /tmp/csql.conf
cp $CSQL_CONFIG_FILE /tmp
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
isql  $DS < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1
if [ $? -ne 0 ]
 then
 exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1=1" -f "f1,f3,f5" 
if [ $? -ne 0 ]
then
 rm -f /tmp/csql/csqltable.conf
 touch /tmp/csql/csqltable.conf
 
 $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
 isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
 exit 2;
fi

isql $DS < ${REL_PATH}/frecords.sql >/dev/null 2>&1

# again reload table  with -r option.
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf

   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 3;
fi

#after reload, select from t1
echo "after reload , select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
if [ $? -ne 0 ]
 then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 5;
fi
 
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;
