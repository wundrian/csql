#!/bin/ksh
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/noindex_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/equijoin4_with_and_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 3;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 4;
fi
