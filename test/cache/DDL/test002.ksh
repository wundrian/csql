#!/bin/ksh

#  create table t1 in csql and TDB. Recover t1.
#  It should fail saying table already exists

CSQL_CONF=${PWD}/cache/DDL/csql.conf
input=${PWD}/cache/DDL/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/DDL
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

DS="$DSN $DBUSER $PASSWORD"
echo DSN=$DSN >>$CSQL_CONFIG_FILE
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi


if [ $DSN = "oracle" ] 
then
   isql $DS < $REL_PATH/oratest1.oracle > /dev/null 2>&1
elif [ "$DSN" = "sybase" ]
then
   isql $DS < $REL_PATH/sybaseinputtest1.sql > /dev/null 2>&1
elif [ "$DSN" = "db2" ]
then
   isql $DS < $REL_PATH/db2inputtest1.sql > /dev/null 2>&1
else
   isql $DS < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "1 t1 NULL NULL NULL $DSN" >/tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver -c > /dev/null 2>&1 &
pid=$!
sleep 5
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql 2> $0.valgrelse
else
    $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinputtest1.sql 
fi
isql $DS < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql
fi
    
kill -9 $pid 
ipcrm -M 1199 -M 2277 -M 1947
exit 0;
