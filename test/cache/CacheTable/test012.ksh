#!/bin/ksh
# Test Case

# Create table t1 and t2 in mysql and insert 10 records each. 
# Cache the tables into csql with -R option. 
# Remove 5 entries from table t1 in csql and 5 entries from table t2 in mysql. 
# Reload both tables with -r option. 
# CSQL now should have 10 entries in t1 and 5 entries in t2 

input=${PWD}/cache/CacheTable/create.sql
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

isql $DS < ${REL_PATH}/create.sql >/dev/null 2>&1
echo table t1 and t2 are created with records in target db

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# write to the csqltable.conf file
echo "1 t1 NULL NULL NULL $DSN" > /tmp/csql/csqltable.conf
echo "2 t2 NULL t2f1>5 NULL $DSN" >> /tmp/csql/csqltable.conf

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/cachetable -R 2> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/cachetable -R 
    if [ $? -ne 0 ]
    then
        cp /tmp/csql.conf $CSQL_CONFIG_FILE
        exit 2;
    fi
fi
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 2> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 
fi
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/deletefromt1csql.sql 2>> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/deletefromt1csql.sql 
fi
isql $DS < $REL_PATH/deletefromt2mysql.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r 2>> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/cachetable -t t1 -r 
    if [ $? -ne 0 ]
    then
        cp /tmp/csql.conf $CSQL_CONFIG_FILE
        exit 2;
    fi
fi
echo table t1 reloaded
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/cachetable -t t2 -r 2>> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/cachetable -t t2 -r 
    if [ $? -ne 0 ]
    then
        cp /tmp/csql.conf $CSQL_CONFIG_FILE
        exit 3;
    fi
fi
echo table t2 reloaded

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 2>> $0.valgr 
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql 
fi
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

