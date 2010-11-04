#!/bin/ksh
# Test Case
# 9. Create table t1 in mysql with primary key. Insert 10 rows. 
#    Cache the table in csql. 
#    Update 2 rows in csql and 2 rows in mysql with different primary keys. 
#    Run $ cacheverify -t t1. 
#        The output should display number of records as 10 for both csql and 
#        mysql respectively.
#    Run $ cacheverify -t t1 -p. 
#        The output should display no missing records in either of the 
#        databases.
#    Run $ cacheverify -t t1 -f. 
#        The output should display the 4 inconsistent records. 
#        Only those fields with different values should be displayed 
#        for inconsistent records.   

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
echo DSN=$DSN >>$CSQL_CONFIG_FILE
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
  isql $DS < ${REL_PATH}/mysqlinput.sql >/dev/null 2>&1
  if [ $? -ne 0 ]
   then
     exit 1;
   fi
elif [ "$DSN" = "oracle" ]
then
   isql $DS < ${REL_PATH}/oracleinput.sql >/dev/null 2>&1
   if [ $? -ne 0 ]
   then
     exit 1;
   fi
elif [ "$DSN" = "sybase" ]
then
   isql $DS < ${REL_PATH}/oracleinput.sql >/dev/null 2>&1
   if [ $? -ne 0 ]
   then
     exit 1;
   fi
elif [ "$DSN" = "db2" ]
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

if [ "$DSN" = "oracle" ]
then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqloracleinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
       exit 2;
    fi
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/mysqlinput.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
       exit 2;
    fi
fi
echo "1 t1 NULL NULL NULL $DSN" > /tmp/csql/csqltable.conf


if [ "$DSN" = "oracle" ]
then
    isql $DS < ${REL_PATH}/oracleupdate.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
        rm -f /tmp/csql/csqltable.conf
        touch /tmp/csql/csqltable.conf
        isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
        exit 3;
    fi
else
    if [ $DSN = "db2" ]
    then 
        isql $DS  < ${REL_PATH}/db2update.sql >/dev/null 2>&1
        if [ $? -ne 0 ]
        then
           isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
           exit 3;
        fi
    else
        isql $DS < ${REL_PATH}/mysqlupdate.sql >/dev/null 2>&1
        if [ $? -ne 0 ]
        then
           isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
           exit 3;
        fi
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlupdate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    echo $?
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 5;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 6;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 7;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1

exit 0;
