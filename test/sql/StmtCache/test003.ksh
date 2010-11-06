#!/bin/ksh
# Update and Delete statement with one parameter should be cached
CREATEFILE=${PWD}/sql/StmtCache/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/StmtCache
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/t1.sql >/dev/null 2>&1


if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $REL_PATH/stmtTest3
else 
    $REL_PATH/stmtTest3 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql 
       exit 1;
    fi
fi
$CSQL_INSTALL_ROOT/bin/csqldump
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1
rm -f ${REL_PATH}/dropt1.sql 

exit 0;
