#!/bin/sh
#Test Case
#17. Create table t1 and t2 in target DB with 10 records.
#    Recover the two tables from the target DB with -R option,
#    as per the csqltable.conf file.
#    the contains in csqltable.conf file is: 
#      				1:t1 NULL
#				2:t2 t2f1<5

#Run this test only under csql/test or on this directory
#otherwise it may fail.

#AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1,t2 in target DB.
isql $DSN < ${REL_PATH}/create.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 1;
fi
echo Table t1 and t2 created in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db


echo "1:t1 NULL NULL NULL"  > /tmp/csql/csqltable.conf 
echo "2:t2 NULL t2f1<5 NULL" >> /tmp/csql/csqltable.conf     
        
      	

# caching with -R option
$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
   isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf  /tmp/csql/csql.db
   touch  /tmp/csql/csqltable.conf /tmp/csql/csql.db
   exit 3;
fi

rm -f /tmp/csql/csqltable.conf  /tmp/csql/csql.db
touch  /tmp/csql/csqltable.conf /tmp/csql/csql.db
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1t2.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/dropt1t2.sql >/dev/null 2>&1

exit 0;


