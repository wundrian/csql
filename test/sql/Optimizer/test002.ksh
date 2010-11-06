#!/bin/ksh
# Test Case 
# create hash index on f1 and tree index on f2 and no index on f3
# Multiple Predicates
# 1)Single table equi predicate with f1 and f3 should use hash scan
# 2)Single table range predicate on f1  and equi on f3 should use tree scan
# 3)Single table equi on f3 and range predicate on f1 should use tree scan
# Disjunctive predicates
# 4)Single table nonequi predicate on f1 should use full scan
# 5)Single table nonequi predicate on f2 should use full scan
# 6)Single table f1=10 or f3=20 should use full scan
# 7)Single table f2>10 or f3=20 should use full scan
# 8)Single table f3=20 or f2 >10 should use full scan
QUITFILE=${PWD}/sql/Optimizer/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Optimizer
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2t3.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/singletabletest2.sql 
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
  exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
 exit 0;

