#!/bin/ksh
# Testing simple left join on two table with integers
#
CREATEFILE=${PWD}/sql/OuterJoin/dropt1t2.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/OuterJoin
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
   exit 3;
fi

exit 0;
