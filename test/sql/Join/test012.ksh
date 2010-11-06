#!/bin/ksh
# Test Case 
#create three tables as:
#create table emp(eno int,mgrno int,sal float,deptno int);
#create table dept(deptno int,dname char(10),lid int);
#create table loc(lid int,state char(10));
#Insert valid records into the 3 tables. Insert NULL values in some of the field
#select * from emp,dept,loc where emp.deptno!=dept.deptno AND dept.lid!=loc.lid;
#select * from emp,dept,loc where NOT(emp.deptno!=dept.deptno AND dept.lid!=loc.lid);
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join31.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
