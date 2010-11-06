#!/bin/ksh
# Testing LIKE operator in Join
#create table emp(eno int,ename char(10),dno int);
#create table dept(deptno int,dname char(10),lid int);
#Insert some records into both the tables.
#Test the following Select statements using join and BETWEEN operator and check the retrieved data are proper or not
# select * from emp where emp.deptno in (20,30,40); here emp.deptno is non existing field.
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join34.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join_in_notexist.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_emp_dept.sql 
if [ $? -ne 0 ]
then
  exit 1;
fi
