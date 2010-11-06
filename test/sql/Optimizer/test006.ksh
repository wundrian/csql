#!/bin/ksh
# IN, BETWEEN and LIKE operator test on Tree Index
# Create table with all datatypes
# create simple tree index on each datatypes.
# Apply explain plan using select with where clause. (in,between,like predicates)
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tree_inbetweenlike.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tree_inbetweenlike.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

