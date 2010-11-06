#!/bin/ksh
#Test Case
# CREATE TABLE T1(f1 int,f2 int,f3 int,f4 int,f5 int);
#CREATE INDEX idx1 on T1(f2);
#CREATE INDEX idx2 on T1(f3);
#CREATE INDEX idx3 on T1(f4);
#CREATE INDEX idx4 on T1(f5);
#CREATE TABLE T2(f1 int,f2 int,primary key(f2));
#CREATE TABLE T3(f1 int,f3 int,primary key(f3));
#CREATE TABLE T4(f1 int,f4 int,primary key(f4));
#CREATE TABLE T5(f1 int,f5 int,primary key(f5));
#
#2) Insert 10k records in T1,
#1k records in T2
#1k records in T3
#1k records in T4
#1k records in T5
#
#3) Execute the following join statements.
#select COUNT(*) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
#select SUM(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
#select MIN(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
#select AVG(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
#select MAX(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
#

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/bigtable.sql
if [ $? -ne 0 ]
 then
   exit 1;
fi
for (( i=1 ; i<=10000 ; i++ ))
do
 echo "insert into T1 values ($i,$i,$i,$i,$i);" >>$REL_PATH/T1.sql
done 

for (( i=1 ; i<=1000 ; i++ ))
do
 echo "insert into T2 values($i,$i);" 
 echo "insert into T3 values($i,$i);" 
 echo "insert into T4 values($i,$i);" 
 echo "insert into T5 values($i,$i);" 
done >>$REL_PATH/T11.sql

for (( i=1 ; i<=5 ; i++ ))
do
echo "DROP TABLE T$i;"
done >>$REL_PATH/drop_all_table.sql


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/T1.sql >/dev/null 2>&1 
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_all_table.sql
    rm -f $REL_PATH/T1.sql $REL_PATH/T11.sql $REL_PATH/drop_all_table.sql
    exit 2;
 fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/T11.sql >/dev/null 2>&1
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_all_table.sql
    rm -f $REL_PATH/T1.sql $REL_PATH/T11.sql $REL_PATH/drop_all_table.sql
    exit 3;
 fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -s $REL_PATH/all_agg.sql
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_all_table.sql
    rm -f $REL_PATH/T1.sql $REL_PATH/T11.sql $REL_PATH/drop_all_table.sql
    exit 4;
 fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_all_table.sql
rm -f $REL_PATH/T1.sql $REL_PATH/T11.sql $REL_PATH/drop_all_table.sql
exit 0;

