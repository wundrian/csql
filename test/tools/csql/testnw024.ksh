#!/bin/ksh
# Test Case
# 35. Create table (f1 int, f2 bigint, f3 smallint,f4 tinyint); 
#     Insert 5 tuples 
#     Then create index in different combination 
#     All Should be fail with unique key violation error.

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/uniqueindex.sql 
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/drop.sql
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csqldump -T t1
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi
exit 0;
