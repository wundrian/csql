#!/bin/sh
# Test Case
# Create table t1 having two field f1 char and f2 int with primary key f1 and create table t2 having two integer field f1,f2 with foreign key f1 refers t1 (f1). It should fail due to type mismatch in FK and PK table
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi


echo "CREATE TABLE t1(f1 CHAR(10),f2 INT,PRIMARY KEY(f1));" >${REL_PATH}/fkey1.sql
echo "CREATE TABLE t2(f1 INT,f2 INT,FOREIGN KEY(f1) REFERENCES t1(f1));" >${REL_PATH}/fkey2.sql
echo "drop table t1;" >${REL_PATH}/drp1.sql
echo "drop table t2;" >${REL_PATH}/drp2.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/fkey1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/fkey1.sql
   rm -f ${REL_PATH}/fkey2.sql
   rm -f ${REL_PATH}/drp1.sql
   rm -f ${REL_PATH}/drp2.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/fkey2.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp1.sql
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp2.sql
   rm -f ${REL_PATH}/fkey1.sql
   rm -f ${REL_PATH}/fkey2.sql
   rm -f ${REL_PATH}/drp1.sql
   rm -f ${REL_PATH}/drp2.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drp1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/fkey1.sql
   rm -f ${REL_PATH}/fkey2.sql
   rm -f ${REL_PATH}/drp1.sql
   rm -f ${REL_PATH}/drp2.sql
   exit 3;
fi

rm -f ${REL_PATH}/fkey1.sql
rm -f ${REL_PATH}/fkey2.sql
rm -f ${REL_PATH}/drp1.sql
rm -f ${REL_PATH}/drp2.sql
exit 0;
