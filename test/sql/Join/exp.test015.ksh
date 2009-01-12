Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from emp,dept;
---------------------------------------------------------
	eno	ename	dno	deptno	dname	
---------------------------------------------------------
	1	Nihar	10	20	Sales	
	1	Nihar	10	40	Mkt	
	1	Nihar	10	35	HR	
	2	Kishore	20	20	Sales	
	2	Kishore	20	40	Mkt	
	2	Kishore	20	35	HR	
	3	Jiten	30	20	Sales	
	3	Jiten	30	40	Mkt	
	3	Jiten	30	35	HR	
	4	Bijay	40	20	Sales	
	4	Bijay	40	40	Mkt	
	4	Bijay	40	35	HR	
	5	Kailash	50	20	Sales	
	5	Kailash	50	40	Mkt	
	5	Kailash	50	35	HR	
	
echo select * from emp,dept where emp.ename LIKE 'K%';
---------------------------------------------------------
	eno	ename	dno	deptno	dname	
---------------------------------------------------------
	2	Kishore	20	20	Sales	
	2	Kishore	20	40	Mkt	
	2	Kishore	20	35	HR	
	5	Kailash	50	20	Sales	
	5	Kailash	50	40	Mkt	
	5	Kailash	50	35	HR	
	
echo select * from emp,dept where dept.dname LIKE 'S%';
---------------------------------------------------------
	eno	ename	dno	deptno	dname	
---------------------------------------------------------
	1	Nihar	10	20	Sales	
	2	Kishore	20	20	Sales	
	3	Jiten	30	20	Sales	
	4	Bijay	40	20	Sales	
	5	Kailash	50	20	Sales	
	
echo select * from emp,dept where emp.ename LIKE 'K%' and dept.dname LIKE 'S%';
---------------------------------------------------------
	eno	ename	dno	deptno	dname	
---------------------------------------------------------
	2	Kishore	20	20	Sales	
	5	Kailash	50	20	Sales	
	
echo select * from emp,dept where emp.ename LIKE 'K%' or dept.dname LIKE 'S%';
---------------------------------------------------------
	eno	ename	dno	deptno	dname	
---------------------------------------------------------
	1	Nihar	10	20	Sales	
	2	Kishore	20	20	Sales	
	2	Kishore	20	40	Mkt	
	2	Kishore	20	35	HR	
	3	Jiten	30	20	Sales	
	4	Bijay	40	20	Sales	
	5	Kailash	50	20	Sales	
	5	Kailash	50	40	Mkt	
	5	Kailash	50	35	HR	
	
echo drop table emp;
Statement Executed
echo drop table dept;
Statement Executed
