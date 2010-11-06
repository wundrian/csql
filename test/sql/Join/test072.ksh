#!/bin/ksh
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/composite3.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert_t1_t2.sql
if [ $? -ne 0 ]
then
  exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join36.sql
if [ $? -ne 0 ]
then
  exit 3;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_t1_t2.sql
if [ $? -ne 0 ]
then
  exit 3;
fi
