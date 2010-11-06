#!/bin/ksh
#  NOT NULL Constraint test on varchar
#  Create table t1( f1 int, f2 varchar(15) NOT NULL);
#  Insert 5 records into t1 having null values in f1 for some of the records.
#  Null value should not be inserted into varchar field.
#  Update Records set NULL value to varchar field. It should not be allowed
#  Retrieve records based on varchar field.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "echo Create table t1( f1 int, f2 varchar(15) NOT NULL);" >${REL_PATH}/varchar_NOTNULL.sql
echo "Create table t1( f1 int, f2 varchar(15) NOT NULL);" >>${REL_PATH}/varchar_NOTNULL.sql
echo "insert into t1 values(1,'Lakshya1');" >>${REL_PATH}/varchar_NOTNULL.sql
echo "insert into t1 values(2,NULL);" >>${REL_PATH}/varchar_NOTNULL.sql
echo "insert into t1 values(3,'Lakshya3');" >>${REL_PATH}/varchar_NOTNULL.sql
echo "insert into t1 values(4,NULL);" >>${REL_PATH}/varchar_NOTNULL.sql
echo "insert into t1 values(5,'Lakshya5');" >>${REL_PATH}/varchar_NOTNULL.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar_NOTNULL.sql
echo "select * from t1;" >>${REL_PATH}/varchar_NOTNULL.sql
echo "echo update t1 set f2=NULL where f1<=3;" >>${REL_PATH}/varchar_NOTNULL.sql
echo "update t1 set f2=NULL where f1<=3;" >>${REL_PATH}/varchar_NOTNULL.sql
echo "echo select * from t1;" >>${REL_PATH}/varchar_NOTNULL.sql
echo "select * from t1;" >>${REL_PATH}/varchar_NOTNULL.sql

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_NOTNULL.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_NOTNULL.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/varchar_NOTNULL.sql ${REL_PATH}/dropt1.sql
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

rm -f ${REL_PATH}/varchar_NOTNULL.sql ${REL_PATH}/dropt1.sql
exit 0;
