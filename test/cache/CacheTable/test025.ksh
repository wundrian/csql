#!/bin/sh
#Test case 25.
#	Create table t1 in target database.
#	load t1 table with condition and field mode option.
#	unload the t1 table with -u option.

#Run this test nly under csql/test or on this derectory.
#otherwise, it mat fail.

#AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
 if [ -s "$input" ]
 then
     REL_PATH=${PWD}/cache/CacheTable
fi

# create table t1 in target DB.
isql myodbc3 < ${REL_PATH}/fmodeinsert.sql >/dev/null 2>&1
if [ $? -ne 0 ]
  then
    exit 1;
fi

echo Table t1 created in target DB.

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

echo "cachetable -t t1 -c \"f1<3\" -f \"f1,f3,f5\""
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -c "f1<3" -f "f1,f3,f5" >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db

   exit 2;
fi

echo "select from t1 table"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectt1.sql
 if [ $? -ne 0 ]
   then
     rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
     touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
        
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
     isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
       
     exit 4;
fi


$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u >/dev/null 2>&1
 if [ $? -ne 0 ]
 then
     rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
     touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
  
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql >/dev/null 2>&1
     isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
  
     exit 4;
fi

echo "Table t1 unloaded from CSQL"


rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql myodbc3 <${REL_PATH}/drop.sql >/dev/null 2>&1
 exit 0; 




