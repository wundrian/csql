#!/bin/ksh
# drop table should remove all the cached statements which are not in use
CREATEFILE=${PWD}/sql/StmtCache/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/StmtCache
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql
echo "drop table t2;" >>${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/t1.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/t2.sql >/dev/null 2>&1


if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $REL_PATH/stmtTest6
else 
    $REL_PATH/stmtTest6 
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
