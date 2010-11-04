#!/bin/ksh
# Test Case

# 8. For the previous scenario update 2 rows in csql and update 2 rows in mysql with different primary keys.
#    Run $ cacheverify -t t1. 
#        The output should display number of records as 7 and 8 for csql 
#        and mysql respectively.
#    Run $ cacheverify -t t1 -p. 
#        The output should display the primary key field values for missing 
#        records in either of the databases in ascending order.
#    Run $ cacheverify -t t1 -f. 
#        The output should display the 4 inconsistent records.  Only those 
#        fields with different values should be displayed for inconsistent 
#        records.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
 
input=${PWD}/cache/CacheVerify/csqlupdate.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheVerify
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/csqlupdate.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 1;
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

if [ $DSN = "oracle" ]
then
    isql $DS  < ${REL_PATH}/oracleupdate.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
       exit 2;
    fi
else
    if [ $DSN = "db2" ]
    then
        isql $DS  < ${REL_PATH}/db2update.sql >/dev/null 2>&1
        if [ $? -ne 0 ]
        then
           isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
           exit 2;
        fi
    else
        isql $DS < ${REL_PATH}/mysqlupdate.sql >/dev/null 2>&1
        if [ $? -ne 0 ]
        then
           isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
           exit 2;
        fi
    fi
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -p
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 4;
fi

$CSQL_INSTALL_ROOT/bin/cacheverify -t t1 -f
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf
    touch /tmp/csql/csqltable.conf
    isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
    exit 5;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $REL_PATH/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1

exit 0;
