#!/bin/ksh
# Explain plan on all datatypes with single predicate applying tree index(Relational Operators).
# Create table with all datatypes
# Create simple tree index on each datatypes.
# Apply explain plan on each datatypes using select with where clause.
#
QUITFILE=${PWD}/sql/Optimizer/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Optimizer
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tree_singleprrdicate.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tree_singleprrdicate.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

