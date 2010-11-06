#!/bin/ksh
# Testing Join on 5 sales tables.
# Create table with all datatypes except float and double.
# Insert 16 records.
# Select records using Group by.
# Select records using Group by and having.
# Test group by on NULL fields.
# Test Aggregate min() on char,date, time and timestamp.
# Select records using Group by on multiple fields and having on min(). .
#
QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/alldatatype.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s ${REL_PATH}/char_datetypes_min.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
