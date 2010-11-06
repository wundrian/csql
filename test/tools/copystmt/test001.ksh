#!/bin/ksh
#create table t1 with f1 int and f2 char(20). insert 10 different record.
# a. create a copy of table t1 [ create table ct1 as select * from t1]
# b. create a conditional copy of table t1 [create table ct2 as select * from t1 where f1 < conditon]
# c. create a copy of table t1 [create table ct3 as select f2 from t1]
# d. create a copy of table t1 [create table ct4 as select f2 from t1 where f1 < conditon ]
# Drop all tables. 
#
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

echo "echo create table ct1 as select * from t1;" >${REL_PATH}/create_ct1.sql
echo "create table ct1 as select * from t1;"     >>${REL_PATH}/create_ct1.sql

echo "echo create table ct2 as select * from t1 where f1 < 6;" >${REL_PATH}/create_ct2.sql
echo "create table ct2 as select * from t1 where f1 < 6;"     >>${REL_PATH}/create_ct2.sql

echo "echo create table ct3 as select f2 from t1;" >${REL_PATH}/create_ct3.sql
echo "create table ct3 as select f2 from t1;"     >>${REL_PATH}/create_ct3.sql

echo "echo create table ct4 as select f2 from t1 where f1 >3 and f1 <8;" >${REL_PATH}/create_ct4.sql 
echo "create table ct4 as select f2 from t1 where f1 >3 and f1 <8;"     >>${REL_PATH}/create_ct4.sql 

echo "Drop table t1;"  >${REL_PATH}/drop.sql
echo "Drop table ct1;">>${REL_PATH}/drop.sql
echo "Drop table ct2;">>${REL_PATH}/drop.sql
echo "Drop table ct3;">>${REL_PATH}/drop.sql
echo "Drop table ct4;">>${REL_PATH}/drop.sql

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t1.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_t1.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
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
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
       exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full  $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct2.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct2.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
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
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql 
       exit 4;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct4.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_ct4.sql
    if [ $? -ne 0 ]
    then
       echo Failed
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
       exit 5;
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
       rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
       exit 6;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
rm -f ${REL_PATH}/create_t1.sql ${REL_PATH}/create_ct1.sql.sql ${REL_PATH}/create_ct2.sql ${REL_PATH}/create_ct3.sql ${REL_PATH}/create_ct4.sql ${REL_PATH}/drop.sql
echo passed
exit 0;
