#!/bin/sh
#Testing LIKE operator in Join
#create table emp(eno int,ename char(10),dno int);
#create table dept(deptno int,dname char(10));
#insert some records into both the tables.
#Test the following Select statements using join and BETWEEN operator and check the retrieved data are proper or not
#select * from emp,dept where emp.ename LIKE 'K%';
#select * from emp,dept where dept.dname LIKE 'S%';
#select * from emp,dept where emp.ename LIKE 'K%' and dept.dname LIKE 'S%';
#select * from emp,dept where emp.ename LIKE 'K%' or dept.dname LIKE 'S%';
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join33.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join_like.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_emp_dept.sql 
if [ $? -ne 0 ]
then
  exit 1;
fi
