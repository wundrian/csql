#!/bin/ksh
# Copystatement test.
# Create table t1(f1 int, f2 varchar(10), f3 char(10), f4 varchar(10));
# Create table t2 as select f2,f1,f4 from t1;
# Run catalog tool for check the indexes are made properly or not.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo Create table t1(f1 int, f2 varchar(10), f3 char(10), f4 varchar(10));" >${REL_PATH}/varchar_copystmt.sql
echo "Create table t1(f1 int, f2 varchar(10), f3 char(10), f4 varchar(10));" >>${REL_PATH}/varchar_copystmt.sql
echo "echo Create table t2 as select f2,f1,f4 from t1;" >>${REL_PATH}/varchar_copystmt.sql
echo "Create table t2 as select f2,f1,f4 from t1;" >>${REL_PATH}/varchar_copystmt.sql
echo "echo show tables;" >>${REL_PATH}/varchar_copystmt.sql
echo "show tables;" >>${REL_PATH}/varchar_copystmt.sql

echo "drop table t1;" >${REL_PATH}/drop.sql
echo "drop table t2;" >>${REL_PATH}/drop.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_copystmt.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_copystmt.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql
       rm -f ${REL_PATH}/varchar_copystmt.sql ${REL_PATH}/drop.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/varchar_copystmt.sql ${REL_PATH}/drop.sql
exit 0;
