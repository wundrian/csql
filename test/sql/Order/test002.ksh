#!/bin/ksh
# Test order by on left joined tables.
#
CREATEFILE=${PWD}/sql/Order/drop_Articles_Authors_AuthorArticle.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Order
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/leftjoin2.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_Articles_Authors_AuthorArticle.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop_Articles_Authors_AuthorArticle.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

exit 0;
