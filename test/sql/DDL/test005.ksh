#!/bin/ksh
# create trie index with existing records
#
QUITFILE=${PWD}/sql/DDL/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/DDL
fi

echo "drop table t1;">>${REL_PATH}/dropt1.sql

echo "create table t1 ( f1 int not null);" >${REL_PATH}/createt1.sql
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createt1.sql >/dev/null 2>&1
echo "insert into t1 values (10);" >${REL_PATH}/insertt1.sql
echo "insert into t1 values (100);" >>${REL_PATH}/insertt1.sql
echo "insert into t1 values (1000);" >>${REL_PATH}/insertt1.sql
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/insertt1.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/create_trie.sql
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I idx
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
rm -f ${REL_PATH}/createt1.sql
exit 0;

