#!/bin/ksh
# Tree Index, Unique Tree Index
# create table t1 (f1 varchar(10), f2 smallint);
# create table t2 (f1 varchar(10), f2 smallint);
# create index idx1 on t1(f1)tree;
# create index idx2 on t2(f1)tree unique;
# insert records into both the tables.
# t2.f1 field should not allow duplicate records.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "drop table t1;" >${REL_PATH}/drop.sql
echo "drop table t2;" >>${REL_PATH}/drop.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_tree.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_tree.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql
       rm -f ${REL_PATH}/drop.sql
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

rm -f ${REL_PATH}/drop.sql
exit 0;
