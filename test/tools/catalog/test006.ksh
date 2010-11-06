#!/bin/ksh
# Test Case
#create table t2 (f1,f2,f3) ,with primary key(f1) and index on f3 .check with -D chunk 
#insert 20 tuples and check with -D chunk
#delete 10 tuples and check with -D chunk
#drop t2 check with -D chunk

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
sleep 5

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/create1.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/create1.sql 
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
echo "Table  created"

echo "Case 1: With -D chunk  option after table creation:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/insert.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/insert.sql 
    if [ $? -ne 0 ]
    then
       exit 3;
    fi
fi

echo "Tuples insered"
echo "Case 2: With -D chunk  option after insert 20 tuples:"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 4;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/delete.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/delete.sql 
    if [ $? -ne 0 ]
    then
       exit 5;
    fi
fi

echo "10 tuples deleted"

echo "Case 3: With -D chunk option after deleting 10 tuples :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 6;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/dropIndex.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/dropIndex.sql 
    if [ $? -ne 0 ]
    then
       exit 7;
    fi
fi
echo "Index droped"

echo "Case 4: With -D chunk  option after Index droped :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 8;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/dropt2.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/dropt2.sql 
    if [ $? -ne 0 ]
    then
       exit 9;
    fi
fi
echo "t2 table droped with index"

echo "Case 5: With -D chunk  option after drop t2 :"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       exit 10;
    fi
fi

kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;
