#!/bin/ksh
# Testing rollback after truncating table in autocommit off mode.
# Create table t1 with all datatypes.
# Set autocommit off; 
# insert 2 - 3 records into it.
# Execute truncate table t1;
# Rollback the transaction.
# There should not be any record in the table. That means after truncate rollback has no effect.
#
QUITFILE=${PWD}/sql/DDL/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/DDL
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aucommitoff_truncate_rollback.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aucommitoff_truncate_rollback.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

