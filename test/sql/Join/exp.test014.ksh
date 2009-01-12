Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from emp;
---------------------------------------------------------
	eno	dno	
---------------------------------------------------------
	1	10	
	2	20	
	4	40	
	
echo select * from dept;
---------------------------------------------------------
	deptno	dname	
---------------------------------------------------------
	20	Sales	
	30	IT	
	40	Mkt	
	50	HR	
	
echo select * from emp,dept;
---------------------------------------------------------
	eno	dno	deptno	dname	
---------------------------------------------------------
	1	10	20	Sales	
	1	10	30	IT	
	1	10	40	Mkt	
	1	10	50	HR	
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	2	20	50	HR	
	4	40	20	Sales	
	4	40	30	IT	
	4	40	40	Mkt	
	4	40	50	HR	
	
echo select * from emp,dept where emp.dno between 10 and 30;
---------------------------------------------------------
	eno	dno	deptno	dname	
---------------------------------------------------------
	1	10	20	Sales	
	1	10	30	IT	
	1	10	40	Mkt	
	1	10	50	HR	
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	2	20	50	HR	
	
echo select * from emp,dept where dept.deptno between 20 and 40;
---------------------------------------------------------
	eno	dno	deptno	dname	
---------------------------------------------------------
	1	10	20	Sales	
	1	10	30	IT	
	1	10	40	Mkt	
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	4	40	20	Sales	
	4	40	30	IT	
	4	40	40	Mkt	
	
echo select * from emp,dept where emp.dno between 15 and 30  and dept.deptno between 20 and 40;
---------------------------------------------------------
	eno	dno	deptno	dname	
---------------------------------------------------------
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	
echo drop table emp;
Statement Executed
echo drop table dept;
Statement Executed
