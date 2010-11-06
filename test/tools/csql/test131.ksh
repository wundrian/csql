#!/bin/ksh
# Testing tree undolog 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

rm -f /tmp/csql.conf
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "drop table t1;" > ${REL_PATH}/dropp_t1.sql
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/treeundolog1.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/treeundolog1.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
       rm -f ${REL_PATH}/dropp_t1.sql
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
       rm -f ${REL_PATH}/dropp_t1.sql
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/treeundolog2.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/treeundolog2.sql
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
       rm -f ${REL_PATH}/dropp_t1.sql
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       exit 3;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
       rm -f ${REL_PATH}/dropp_t1.sql
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       exit 4;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropp_t1.sql
if [ $? -ne 0 ]
then
   rm -f ${REL_PATH}/dropp_t1.sql
   exit 5;
fi
rm -f ${REL_PATH}/dropp_t1.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
