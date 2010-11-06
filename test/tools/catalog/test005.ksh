#!/bin/ksh
# Test Case
# check options -D chunk with empty database
#create table t1 (f1,f2) check with -D chunk
#drop t1  check with -D chunk

CSQL_CONF=${PWD}/tools/catalog/csql.conf
input=${PWD}/tools/catalog/create.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/catalog
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 10
echo "Case 1: With -D chunk option with empty database"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/create.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/create.sql 
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

echo "Case 2: With -D chunk  option after table creation:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 3;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropt1.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropt1.sql
    if [ $? -ne 0 ]
    then
       exit 4;
    fi
fi
echo "t1 table droped "

echo "Case 3: With -D chunk  option after drop t1 :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 5;
    fi
fi

kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;

