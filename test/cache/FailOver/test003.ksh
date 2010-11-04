#!/bin/ksh

#  3. SELECT/INSERT/UPDATE/DELETE on MySQL table, when csqlserver is down should pass.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/FailOver/csql.conf
input=${PWD}/cache/FailOver/csqlinput.sql
REL_PATH=.
if [ -s "$input"  -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/FailOver
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

isql $DS < $REL_PATH/dropt1t2.sql > /dev/null 2>&1

if [ $DSN = "oracle" ]
then
   isql $DS < $REL_PATH/orainputt1.oracle >/dev/null 2>&1
elif [ $DSN = "sybase" ] 
then
   isql $DS < $REL_PATH/sybaseinputtest1.sql >/dev/null 2>&1 
elif [ $DSN = "db2" ] 
then
   isql $DS < $REL_PATH/db2inputtest1.sql >/dev/null 2>&1 
else
   isql $DS < $REL_PATH/mysqlinputtest1.sql >/dev/null 2>&1 
fi
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "table t1 inserted into target db"
# edit /tmp/csql/csqltable.conf
echo "csql server is down"
if [ $DSN = "oracle" ]
then
  $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/oracsqlinput.oracle
else
  if [ $DSN = "db2" ]
  then
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqldb2input.sql
  else
      $CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/csqlinput.sql
  fi
fi  

isql $DS < $REL_PATH/dropt1t2.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
exit 0;
