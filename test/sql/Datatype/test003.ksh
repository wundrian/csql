#!/bin/ksh
# Autoincreament should not work on Varchar.
# Create table t1( f1 int, f2 varchar(15) AUTO_INCREMENT);
# This statement execution should be failed.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo Create table t1( f1 int, f2 varchar(15) AUTO_INCREMENT);" >${REL_PATH}/varchar_autoincrement.sql
echo "Create table t1( f1 int, f2 varchar(15) AUTO_INCREMENT);" >>${REL_PATH}/varchar_autoincrement.sql
echo "echo show tables;" >>${REL_PATH}/varchar_autoincrement.sql
echo "show tables;" >>${REL_PATH}/varchar_autoincrement.sql

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_autoincrement.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_autoincrement.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/varchar_autoincrement.sql ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/varchar_autoincrement.sql ${REL_PATH}/dropt1.sql
exit 0;
