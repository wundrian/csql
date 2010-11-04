#!/bin/ksh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

# mysql is not connecting becos odbc.ini does not have anything. 
# try to cache the table created in target db
# it should fail 

CSQL_CONF=${PWD}/cache/Recovery/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
echo $DS
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi


isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
isql $DS < $REL_PATH/createt1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

echo "1 t1 NULL NULL NULL $DSN" > /tmp/csql/csqltable.conf


mv ~/.odbc.ini  /tmp
touch ~/.odbc.ini

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1
if [ $? -ne 0 ]
then
    mv /tmp/.odbc.ini ~
    rm -f /tmp/csql/csqlds.conf
    touch /tmp/csql/csqlds.conf
    isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
    exit 0;
fi
mv /tmp/.odbc.ini  ~
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
isql $DS < $REL_PATH/drop.sql > /dev/null 2>&1
exit 3;
