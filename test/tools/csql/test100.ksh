#!/bin/ksh
# Test Case
# Testing all DML on large size allocate 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/largetable1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drt1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   exit 2;
fi

echo "update t1 set f2='LAKSHYA-CSQL' where f1>=3;"
echo "update t1 set f2='LAKSHYA-CSQL' where f1>=3;" >${REL_PATH}/largetableupdate1.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/largetableupdate1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/largetableupdate1.sql 
   exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selectstar.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/largetableupdate1.sql
   exit 4;
fi

echo "delete from t1 where f1<= 7;"
echo "delete from t1 where f1<= 7;" >${REL_PATH}/largetabledelete1.sql
$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/largetabledelete1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/largetableupdate1.sql ${REL_PATH}/largetabledelete1.sql
   exit 5;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/selectstar.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/largetableupdate1.sql ${REL_PATH}/largetabledelete1.sql
   exit 6;
fi

$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
   rm -f ${REL_PATH}/largetableupdate1.sql ${REL_PATH}/largetabledelete1.sql
   exit 7;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/largetableupdate1.sql ${REL_PATH}/largetabledelete1.sql
   exit 8;
fi
rm -f ${REL_PATH}/largetableupdate1.sql ${REL_PATH}/largetabledelete1.sql
exit 0;
