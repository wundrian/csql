#!/bin/ksh
# Default value testing with varchar.
# Create table t1( f1 int, f2 varchar(15) default 'CSQL');
# Insert 5 records into t1 having null values in f1 for some of the records.
# insert into t1 values(2,NULL); This will put NULL in f2 field.
# update t1 set f2=NULL where f2='Lakshya3'; this will put null in f2 field where f2='Lakshya3' 
# Retrieve records based on varchar field.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_default.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_default.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/dropt1.sql
exit 0;
