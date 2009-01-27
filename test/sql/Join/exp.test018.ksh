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
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	emp.eno	emp.ename	emp.dno	
---------------------------------------------------------
	1	Nihar	10	
	2	Papu	20	
	3	Sima	30	
	4	Nama	40	
	5	Pinu	50	
	
---------------------------------------------------------
	dept.deptno	dept.dname	dept.lid	
---------------------------------------------------------
	20	IT	101	
	40	Sales	102	
	60	Mkt	103	
	30	Store	104	
	
---------------------------------------------------------
	emp.eno	emp.ename	emp.dno	dept.deptno	dept.dname	dept.lid	
---------------------------------------------------------
	1	Nihar	10	20	IT	101	
	1	Nihar	10	40	Sales	102	
	1	Nihar	10	60	Mkt	103	
	1	Nihar	10	30	Store	104	
	2	Papu	20	20	IT	101	
	2	Papu	20	40	Sales	102	
	2	Papu	20	60	Mkt	103	
	2	Papu	20	30	Store	104	
	3	Sima	30	20	IT	101	
	3	Sima	30	40	Sales	102	
	3	Sima	30	60	Mkt	103	
	3	Sima	30	30	Store	104	
	4	Nama	40	20	IT	101	
	4	Nama	40	40	Sales	102	
	4	Nama	40	60	Mkt	103	
	4	Nama	40	30	Store	104	
	5	Pinu	50	20	IT	101	
	5	Pinu	50	40	Sales	102	
	5	Pinu	50	60	Mkt	103	
	5	Pinu	50	30	Store	104	
	
echo select * from emp where emp.dname like 'S%';
Statement prepare failed with error -19
echo select * from emp,dept where emp.dname like 'S%';
Statement prepare failed with error -19
echo drop table emp;
Statement Executed
echo drop table dept;
Statement Executed
