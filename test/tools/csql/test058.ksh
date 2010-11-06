#!/bin/ksh
#Test case
#create table t1(f1 int not null,f2 int,f3 int);
#a) create hash unique index on the first field.
#b) create tree unique index on the same field.
#It should be passed
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree13.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree13.sql
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump -T t1 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump -T t1
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

exit 0;
