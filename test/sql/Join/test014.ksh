#!/bin/ksh
#Testing BETWEEN operator in Join
#create table emp(eno int,dno int);
#create table dept(deptno int,dname char(10));
#insert some records into both the tables.
#Test the following Select statements using join and BETWEEN operator and check the retrieved data are proper or not
#select * from emp,dept where emp.dno between 10 and 30;
#select * from emp,dept where dept.deptno between 20 and 40;
#select * from emp,dept where emp.dno between 15 and 30  and dept.deptno between 20 and 40;
#select * from emp,dept where emp.dno between 15 and 30 or dept.deptno between 20 and 40;
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join32.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join_between.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_emp_dept.sql 
if [ $? -ne 0 ]
then
  exit 1;
fi
