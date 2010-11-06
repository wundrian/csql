#!/bin/ksh
# Testing rename table
#
CREATEFILE=${PWD}/sql/Alter/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Alter
fi

echo "create table t1(f1 int,f2 char(20));" >${REL_PATH}/createtable.sql
echo "insert into t1 values(1,'CSQL_LAKSHYA');" >>${REL_PATH}/createtable.sql
echo "rename table t1 to t2;" >${REL_PATH}/renametable.sql
echo "drop table t1;" >${REL_PATH}/dropt1.sql
echo "drop table t2;" >${REL_PATH}/dropt2.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1 
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt2.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createtable.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createtable.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/renametable.sql
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/dropt2.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l >${REL_PATH}/beforealter 

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/renametable.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/renametable.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt2.sql
       rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/renametable.sql
       rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/dropt2.sql
       exit 2;
    fi
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l >${REL_PATH}/afteralter

diff ${REL_PATH}/beforealter ${REL_PATH}/afteralter
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt2.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

rm -f ${REL_PATH}/createtable.sql ${REL_PATH}/renametable.sql
rm -f ${REL_PATH}/dropt1.sql ${REL_PATH}/dropt2.sql
rm -f ${REL_PATH}/beforealter ${REL_PATH}/afteralter

exit 0;
