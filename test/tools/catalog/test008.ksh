#!/bin/ksh
# Test Case for compact table t1 to compact memory
# check options -d 
#
#

CSQL_CONF=${PWD}/tools/catalog/csql.conf
input=${PWD}/tools/catalog/create.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/tools/catalog
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo "create table t1(f1 int,f2 int,f3 char(2000),primary key(f1));">$REL_PATH/createlargedata.sql
echo "create index t1treeind on t1(f2) tree;">>$REL_PATH/createlargedata.sql
a=1
while [[ $a -lt 5000 ]];do
    echo "insert into t1 values($a,$a,'lakshyacsql');"
    if [ $a -eq 500 ]
    then
        echo "commit;">>$REL_PATH/createlargedata.sql
    fi 
    (( a +=1 ))
done >> $REL_PATH/createlargedata.sql

echo "delete from t1 where f1<4000;" >$REL_PATH/deletelarge.sql
echo "commit;">>$REL_PATH/deletelarge.sql


$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 & 
pid=$!
sleep 10

echo "Case 1: With -d option before table creation:"
echo "============================================"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createlargedata.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/createlargedata.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 2;
    fi
fi

echo "Case 2: With -D chunk option after table creation:"
echo "============================================"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 3;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -U -s ${REL_PATH}/deletelarge.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -U -s ${REL_PATH}/deletelarge.sql
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 4;
    fi
fi

echo "Case 3: With -D chunk  option after record deleted:"
echo "==================================================="
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 5;
    fi
fi
echo "compact table t1;" >${REL_PATH}/compact.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/csql -U -s ${REL_PATH}/compact.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -U -s ${REL_PATH}/compact.sql
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql ${REL_PATH}/compact.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 4;
    fi
fi

echo "Case 4: With -D chunk  option after compact statement :"
echo "======================================="
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D chunk
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql ${REL_PATH}/compact.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 7;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropt1.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dropt1.sql
    if [ $? -ne 0 ]
    then
       rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql ${REL_PATH}/compact.sql
       kill -9 $pid
       ipcrm -M 1199 -M 2277
       exit 8;
    fi
fi

rm -f $REL_PATH/createlargedata.sql $REL_PATH/deletelarge.sql ${REL_PATH}/compact.sql
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;

