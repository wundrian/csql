#!/bin/ksh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/tools/csqldump/csql.conf
executable=${PWD}/tools/csqldump/insert
REL_PATH=.
if [ -s "$executable" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi
rm  
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 8
$REL_PATH/insert >/dev/null 2>&1
if [ $? -ne 0 ]
then 
    exit 1;
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump >tmp.out
    if [ $? -ne 0 ]
    then
        exit 2;
    fi
fi

head -n 13 tmp.out
tail tmp.out
rm -f tmp.out

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql > /dev/null 2>&1
    if [ $? -ne 0 ]
    then
        exit 3;
    fi
fi

kill -9 $pid > /dev/null 2>&1
ipcrm -M 1234 -M 4321

exit 0;
