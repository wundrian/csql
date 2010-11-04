#!/bin/ksh
#Test case 28.
#  create table t1 with records in target DB.
#  create a table with the same schema in csql .
#  load with -s option. it should pass.

#AUTHOR :  Jitendra Lenka

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

isql $DS < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1
if [ "$DSN" = "oracle" ] 
then
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/fcsqlinputoracle.sql > /dev/null 2>&1
else
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/fcsqlinput.sql > /dev/null 2>&1
fi
if [ $? -ne 0 ]
then 
	isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
	rm -f /tmp/csql/csqltable.conf
	touch /tmp/csql/csqltable.conf
	exit 1;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# caching with -s option
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 3;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selectt1.sql
if [ $? -ne 0 ]
then
   rm -f /tmp/csql/csqltable.conf
   touch /tmp/csql/csqltable.conf
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 4;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
 
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;

