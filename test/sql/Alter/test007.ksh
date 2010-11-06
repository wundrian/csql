#!/bin/ksh
# Adding new columns to Existing Table.
# Create table t1(f1 int,f2 char(10));
# Insert a record into t1.
# Alter table t1 add(f3 float);
# Check f3 field of existing record is null or not.
# Run catalog tool to see the shhema.
#
CREATEFILE=${PWD}/sql/Alter/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Alter
fi

echo "create table t1(f1 int,f2 char(20));" >${REL_PATH}/createtable.sql
echo "insert into t1 values(1,'CSQL_LAKSHYA');" >>${REL_PATH}/createtable.sql
echo "echo alter table t1 add(f3 float);" >${REL_PATH}/addcolumn.sql
echo "alter table t1 add(f3 float);" >>${REL_PATH}/addcolumn.sql
echo "echo select * from t1;" >>${REL_PATH}/addcolumn.sql
echo "select * from t1;" >>${REL_PATH}/addcolumn.sql
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
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/addcolumn.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l >${REL_PATH}/beforealter 

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/addcolumn.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/addcolumn.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/addcolumn.sql 
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
   rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/addcolumn.sql
   rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/beforealter ${REL_PATH}/afteralter
   exit 3;
fi

rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/addcolumn.sql
rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/beforealter ${REL_PATH}/afteralter

exit 0;
