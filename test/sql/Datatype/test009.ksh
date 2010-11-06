#!/bin/ksh
# Composite key(HASH) on varchar with other types.
# Create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 float, f8 double,f9 Date, f10 Time, f11 Timestamp);
# create index hashidxtinyvar on t1(f1, f6);
# create index hashidxsmallvar on t1(f2, f6);
# create index hashidxvarint on t1(f6, f3);
# create index hashidxvarbig on t1(f6, f4);
# create index hashidxcharvar on t1(f5, f6);
# create index hashidxvardate on t1(f6, f9);
# create index hashidxvartime on t1(f6, f10);
# create index hashidxvarfloat on t1(f6, f7); should be fail.
# create index hashidxvardouble on t1(f6, f8); should be fail.
# create index hashidxvartimestamp on t1(f6, f11); should be fail.
# Run catalog tool for check the indexes are made properly or not.
#
CREATEFILE=${PWD}/sql/Datatype/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Datatype
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_compindex.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_compindex.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
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

rm -f ${REL_PATH}/dropt1.sql
exit 0;
