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
	emp.eno	emp.dno	
---------------------------------------------------------
	1	10	
	2	20	
	4	40	
	
echo select * from dept;
---------------------------------------------------------
	dept.deptno	dept.dname	
---------------------------------------------------------
	20	Sales	
	30	IT	
	40	Mkt	
	50	HR	
	
echo select * from emp,dept;
---------------------------------------------------------
	emp.eno	emp.dno	dept.deptno	dept.dname	
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
	
echo select * from emp,dept where emp.dno in(20,30);
---------------------------------------------------------
	emp.eno	emp.dno	dept.deptno	dept.dname	
---------------------------------------------------------
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	2	20	50	HR	
	
echo select * from emp,dept where dept.deptno in(20,30);
---------------------------------------------------------
	emp.eno	emp.dno	dept.deptno	dept.dname	
---------------------------------------------------------
	1	10	20	Sales	
	1	10	30	IT	
	2	20	20	Sales	
	2	20	30	IT	
	4	40	20	Sales	
	4	40	30	IT	
	
echo select * from emp,dept where emp.dno in(20,30)  and dept.deptno in(20,30);
---------------------------------------------------------
	emp.eno	emp.dno	dept.deptno	dept.dname	
---------------------------------------------------------
	2	20	20	Sales	
	2	20	30	IT	
	
echo select * from emp,dept where emp.dno in(20,30) or dept.deptno in(20,30);
---------------------------------------------------------
	emp.eno	emp.dno	dept.deptno	dept.dname	
---------------------------------------------------------
	1	10	20	Sales	
	1	10	30	IT	
	2	20	20	Sales	
	2	20	30	IT	
	2	20	40	Mkt	
	2	20	50	HR	
	4	40	20	Sales	
	4	40	30	IT	
	
echo drop table emp;
Statement Executed
echo drop table dept;
Statement Executed
