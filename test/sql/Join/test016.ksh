#!/bin/sh

#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join34.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join_in_notexist.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_emp_dept.sql 
if [ $? -ne 0 ]
then
  exit 1;
fi
