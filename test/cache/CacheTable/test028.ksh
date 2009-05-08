#!/bin/sh
#Test case 28.

#	create table t1 with records in target DB.
#	create a table with the same schema in csql .
#	load with -s option. it should pass.

#AUTHOR :  Jitendra Lenka

input=${PWD}/cache/CacheTable/
REL_PATH=.
if [ -s "$input" ]
then
REL_PATH=${PWD}/cache/CacheTable
fi
cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/fcsqlinput.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then 
	isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
	rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
	touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
	exit 1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

# caching with -s option
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1
if [ $? -ne 0 ]
then
   rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
   touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 3;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selectt1.sql
if [ $? -ne 0 ]
then
   rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
   touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
   isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 4;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;

