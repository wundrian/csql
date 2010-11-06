#!/bin/ksh
# Test Case 
# No Primary key tests
# 1)Single table no predicate should use table scan
# 2)Single table equi predicate on f1 should use table scan
# 3)Single table range predicate on f1 should use table scan
# Primary key tests: create primary hash index on f1
# 4)Single table no predicate should use table scan
# 5)Single table equi predicate on f1 should use hash scan
# 6)Single table range predicate on f1 should use table scan
# Hash Index tests:create hash index on f2
# 7)Single table no predicate should use table scan
# 8)Single table equi predicate on f2 should use hash scan
# 9)Single table range predicate on f2 should use table scan
# Tree Index tests:create tree index on f2
# 10)Single table no predicate should use table scan
# 11)Single table equi predicate on f2 should use tree scan
# 12)Single table range predicate on f2 should use tree scan
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
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/singletabletest1.sql 
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
  exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
 exit 0;

