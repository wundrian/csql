#!/bin/ksh
# Testing Join on 5 sales tables.
# Create table with all datatypes except float and double.
# Insert 20 records with null value in some fields.
# Select records using Group by.
# Select records using Group by and having.
# Select records using Group by on multiple fields in different combination.
# Select records using Group by on multiple fields and having on sum().
# Test group by on NULL fields.
#
QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype_aggregate_sum.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/alldatatype_aggregate_sum.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       exit 2;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
