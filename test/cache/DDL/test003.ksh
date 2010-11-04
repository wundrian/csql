#!/bin/ksh

# Cache table t1 from target database and drop the table. It should give an error.   

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

if [ $DSN = "oracle" ]
then
  isql $DS < $REL_PATH/oratest1.oracle >/dev/null
elif [ "$DSN" = "sybase" ]
then
   isql $DS < $REL_PATH/sybaseinputtest1.sql > /dev/null 2>&1
elif [ "$DSN" = "db2" ]
then
   isql $DS < $REL_PATH/db2inputtest1.sql > /dev/null 2>&1
else
  isql $DS < $REL_PATH/mysqlinputtest2.sql >/dev/null
fi


if [ $? -ne 0 ]
then
    echo "unable to create in target db"
    exit 1
fi

rm   /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/cachetable -t t1 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/cachetable -t t1
    if [ $? -ne 0 ]
    then
        echo "unable to cache table from target db"
        rm   /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
        touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
        isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
        exit 2 
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/dropall.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u
    if [ $? -ne 0 ]
    then
        echo "unable to Unload the table"
        rm   /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
        touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
        isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
        exit 3 
    fi
fi
isql $DS < $REL_PATH/dropall.sql >/dev/null 2>&1
kill -9 $pid 
ipcrm -M 1199 -M 2277 -M 1947
rm   /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
exit 0
