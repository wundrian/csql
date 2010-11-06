#!/bin/ksh
# Dropping an existing column from a Table.
# Create table t1(f1 int,f2 char(10),f3 float);
# Alter table t1 drop column f3;
#
CREATEFILE=${PWD}/sql/Alter/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Alter
fi

echo "create table t1(f1 int,f2 char(20), f3 float);" >${REL_PATH}/createtable.sql
echo "insert into t1 values(1,'CSQL_LAKSHYA',50.5);" >>${REL_PATH}/createtable.sql
echo "echo alter table t1 drop column f3;" >${REL_PATH}/dropcolumn.sql
echo "alter table t1 drop column f3;" >>${REL_PATH}/dropcolumn.sql
echo "echo select * from t1;" >>${REL_PATH}/dropcolumn.sql
echo "select * from t1;" >>${REL_PATH}/dropcolumn.sql
echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1 

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createtable.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createtable.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/dropcolumn.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l >${REL_PATH}/beforealter 

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropcolumn.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropcolumn.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/dropcolumn.sql 
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/beforealter
       exit 2;
    fi
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l >${REL_PATH}/afteralter

diff ${REL_PATH}/beforealter ${REL_PATH}/afteralter

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/dropcolumn.sql
   rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/beforealter ${REL_PATH}/afteralter
   exit 3;
fi

rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/dropcolumn.sql
rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/beforealter ${REL_PATH}/afteralter

exit 0;
