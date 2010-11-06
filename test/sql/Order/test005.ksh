#!/bin/ksh
# Testing Field Format for both Projection list and order by list. 
# Order by <single field> and <multiple fields> in ascending order on single table with where clause 
# Order by <single field> and <multiple fields> in descending order on single table with where clause 
#
CREATEFILE=${PWD}/sql/Order/drop_Articles_Authors_AuthorArticle.sql
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Order
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/table_t1.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/order_single_multiple.sql
if [ $? -ne 0 ]
then
   $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 3;
fi

exit 0;
