#!/bin/ksh
# Alter table test.
# Create table t1(f1 varchar(10), f2 bigint);
# alter table t1 rename column f1 to F1.
# rename table t1 to T1.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo Create table t1(f1 varchar(10), f2 bigint);" >${REL_PATH}/varchar_alter.sql
echo "Create table t1(f1 varchar(10), f2 bigint);" >>${REL_PATH}/varchar_alter.sql
echo "echo alter table t1 rename column f1 to F1;" >>${REL_PATH}/varchar_alter.sql
echo "alter table t1 rename column f1 to F1;" >>${REL_PATH}/varchar_alter.sql
echo "echo rename table t1 to T1;" >>${REL_PATH}/varchar_alter.sql
echo "rename table t1 to T1;" >>${REL_PATH}/varchar_alter.sql
echo "echo show tables;" >>${REL_PATH}/varchar_alter.sql
echo "show tables;" >>${REL_PATH}/varchar_alter.sql

echo "drop table T1;" >${REL_PATH}/dropT1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropT1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_alter.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_alter.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropT1.sql
       rm -f ${REL_PATH}/varchar_alter.sql ${REL_PATH}/dropT1.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropT1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/varchar_alter.sql ${REL_PATH}/dropT1.sql
exit 0;
