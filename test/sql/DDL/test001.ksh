#!/bin/ksh
# Testing truncate command. 
# Create table t1 with all datatypes.
# insert 2 - 3 records into it.
# Execute truncate table t1;
# it should delete all the records. 
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/truncatet1.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/truncatet1.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

