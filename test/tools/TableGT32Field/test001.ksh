#!/bin/sh
# NULL TEST  
# Create a table with more than 32 field.
#  Insert some record with some null values.
#  Check select Statement with is NULL and is not NULL.
#  Update some record to NULL.
#  Again Select with is  NULL.
#  Drop table.
# Author :Bijaya 

QUITFILE=${PWD}/tools/TableGT32Field/create.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/TableGT32Field
fi

if [ "$VALGRIND" = "true" ]
then
   valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql
   if [ $? -ne 0 ]
   then
      exit 1;
   fi
fi

exit 0;
