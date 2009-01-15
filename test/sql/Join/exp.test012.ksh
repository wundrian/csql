echo create table emp(eno int,mgrno int,sal float,deptno int);
Statement Executed
echo insert into emp values(1,3,5000,10);
Statement Executed: Rows Affected = 1
echo insert into emp values(2,4,4000,20);
Statement Executed: Rows Affected = 1
echo insert into emp values(3,NULL,8000,10);
Statement Executed: Rows Affected = 1
echo create table dept(deptno int,dname char(10),lid int);
Statement Executed
echo insert into dept values(10,'IT',100);
Statement Executed: Rows Affected = 1
echo insert into dept values(20,'HR',300);
Statement Executed: Rows Affected = 1
echo create table loc(lid int,state char(10));
Statement Executed
echo insert into loc values(100,'Orissa');
Statement Executed: Rows Affected = 1
echo insert into loc values(200,'Cal');
Statement Executed: Rows Affected = 1
echo insert into loc values(300,'Calif');
Statement Executed: Rows Affected = 1
echo select * from emp;
---------------------------------------------------------
	eno	mgrno	sal	deptno	
---------------------------------------------------------
	1	3	5000.000000	10	
	2	4	4000.000000	20	
	3	NULL	8000.000000	10	
	
echo select * from dept;
---------------------------------------------------------
	deptno	dname	lid	
---------------------------------------------------------
	10	IT	100	
	20	HR	300	
	
echo select * from loc;
---------------------------------------------------------
	lid	state	
---------------------------------------------------------
	100	Orissa	
	200	Cal	
	300	Calif	
	
echo select * from emp,dept,loc;
---------------------------------------------------------
	eno	mgrno	sal	deptno	deptno	dname	lid	lid	state	
---------------------------------------------------------
	1	3	5000.000000	10	10	IT	100	100	Orissa	
	1	3	5000.000000	10	10	IT	100	200	Cal	
	1	3	5000.000000	10	10	IT	100	300	Calif	
	1	3	5000.000000	10	20	HR	300	100	Orissa	
	1	3	5000.000000	10	20	HR	300	200	Cal	
	1	3	5000.000000	10	20	HR	300	300	Calif	
	2	4	4000.000000	20	10	IT	100	100	Orissa	
	2	4	4000.000000	20	10	IT	100	200	Cal	
	2	4	4000.000000	20	10	IT	100	300	Calif	
	2	4	4000.000000	20	20	HR	300	100	Orissa	
	2	4	4000.000000	20	20	HR	300	200	Cal	
	2	4	4000.000000	20	20	HR	300	300	Calif	
	3	NULL	8000.000000	10	10	IT	100	100	Orissa	
	3	NULL	8000.000000	10	10	IT	100	200	Cal	
	3	NULL	8000.000000	10	10	IT	100	300	Calif	
	3	NULL	8000.000000	10	20	HR	300	100	Orissa	
	3	NULL	8000.000000	10	20	HR	300	200	Cal	
	3	NULL	8000.000000	10	20	HR	300	300	Calif	
	
echo select * from emp,dept,loc where emp.deptno!=dept.deptno AND dept.lid!=loc.lid;
---------------------------------------------------------
	eno	mgrno	sal	deptno	deptno	dname	lid	lid	state	
---------------------------------------------------------
	1	3	5000.000000	10	20	HR	300	100	Orissa	
	1	3	5000.000000	10	20	HR	300	200	Cal	
	2	4	4000.000000	20	10	IT	100	200	Cal	
	2	4	4000.000000	20	10	IT	100	300	Calif	
	3	NULL	8000.000000	10	20	HR	300	100	Orissa	
	3	NULL	8000.000000	10	20	HR	300	200	Cal	
	
echo select * from emp,dept,loc where NOT(emp.deptno!=dept.deptno AND dept.lid!=loc.lid);
---------------------------------------------------------
	eno	mgrno	sal	deptno	deptno	dname	lid	lid	state	
---------------------------------------------------------
	1	3	5000.000000	10	10	IT	100	100	Orissa	
	1	3	5000.000000	10	10	IT	100	200	Cal	
	1	3	5000.000000	10	10	IT	100	300	Calif	
	1	3	5000.000000	10	20	HR	300	300	Calif	
	2	4	4000.000000	20	10	IT	100	100	Orissa	
	2	4	4000.000000	20	20	HR	300	100	Orissa	
	2	4	4000.000000	20	20	HR	300	200	Cal	
	2	4	4000.000000	20	20	HR	300	300	Calif	
	3	NULL	8000.000000	10	10	IT	100	100	Orissa	
	3	NULL	8000.000000	10	10	IT	100	200	Cal	
	3	NULL	8000.000000	10	10	IT	100	300	Calif	
	3	NULL	8000.000000	10	20	HR	300	300	Calif	
	
echo drop table emp;
Statement Executed
echo drop table dept;
Statement Executed
echo drop table loc;
Statement Executed
