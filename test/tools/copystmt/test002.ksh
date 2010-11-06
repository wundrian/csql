#!/bin/ksh
#create table t1 with f1 int and f2 char(20). insert 10 different record. 
#create table ct1 with f1 int ,f2 char(20) 
#create table ct2 with f1 int 
#create table ct3 with f1 char(20)
# a. insert into ct1 as select * from t1;
# b. insert into ct2 as select f1 from t1;
# c.insert into ct3 as select f2 from t1;
# Drop all tables.
QUITFILE=${PWD}/tools/copystmt/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/copystmt
fi

echo "echo create table t1(f1 int,f2 char(20));" >${REL_PATH}/create_t1.sql
echo "create table t1(f1 int,f2 char(20));" >>${REL_PATH}/create_t1.sql
i=1
while [ $i -le 10 ]
do
  echo "insert into t1 values($i,'CSQL$i');" >>${REL_PATH}/create_t1.sql
  i=`expr $i + 1`
done

echo "echo create table ct1 (f1 int, f2 char(20));" >${REL_PATH}/create_ct1.sql
echo "create table ct1 (f1 int, f2 char(20));"     >>${REL_PATH}/create_ct1.sql

echo "echo create table ct2(f1 int);" >${REL_PATH}/create_ct2.sql
echo "create table ct2(f1 int);"     >>${REL_PATH}/create_ct2.sql

echo "echo create table ct3(f1 char(20));" >${REL_PATH}/create_ct3.sql
echo "create table ct3(f1 char(20));"     >>${REL_PATH}/create_ct3.sql

echo "echo insert into ct1 as select * from t1;" >${REL_PATH}/insertinto_ct1.sql
echo "insert into ct1 as select * from t1;"     >>${REL_PATH}/insertinto_ct1.sql

echo "echo insert into ct2 as select f1 from t1;" >${REL_PATH}/insertinto_ct2.sql
echo "insert into ct2 as select f1 from t1;"     >>${REL_PATH}/insertinto_ct2.sql

echo "echo insert into ct3 as select f2 from t1;" >${REL_PATH}/insertinto_ct3.sql
echo "insert into ct3 as select f2 from t1;"     >>${REL_PATH}/insertinto_ct3.sql

echo "Drop table t1;"  >${REL_PATH}/drop.sql
echo "Drop table ct1;">>${REL_PATH}/drop.sql
echo "Drop table ct2;">>${REL_PATH}/drop.sql
echo "Drop table ct3;">>${REL_PATH}/drop.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t1.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t1.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct1.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct1.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct2.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct2.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 3;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct3.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct3.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 4;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct1.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct1.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 5;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct2.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct2.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 6;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct3.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insertinto_ct3.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 7;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
       exit 8;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/insertinto_ct1.sql ${REL_PATH}/insertinto_ct2.sql ${REL_PATH}/insertinto_ct3.sql ${REL_PATH}/drop.sql
echo passed
exit 0;
