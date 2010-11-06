#!/bin/ksh
# IN, BETWEEN and LIKE operator test on Hash Index along with '=' operator
# Create table with all datatypes
# create simple hash index on each datatypes.
# Apply explain plan using select with multiple predicates.(in,between,like predicates along with '=' operator).
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
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/hash_multiplepredicate.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/hash_multiplepredicate.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

