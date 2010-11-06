echo create table emp(id int,name char(20),job char(10),salary double,doj date,deptno int,mgrno int);
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from emp;
---------------------------------------------------------
	emp.id	emp.name	emp.job	emp.salary	emp.doj	emp.deptno	emp.mgrno	
---------------------------------------------------------
	1	Allen	Sales	10000.000000	2006/3/3	10	4	
	2	Piter	IT	10000.000000	2005/3/3	20	3	
	3	Jack	Mkting	9000.000000	2006/3/3	30	6	
	4	Tom	Clerk	7000.000000	2004/3/3	10	1	
	5	Harry 	IT	25000.000000	2005/3/3	20	5	
	6	Dick	Sales	15000.000000	2005/3/3	30	7	
	7	Boyee	Mentain	20000.000000	2005/3/3	20	2	
	3	Jack	IT	9000.000000	2006/3/3	30	6	
	2	Piter	Mkting	10000.000000	2005/3/3	20	3	
	
echo select a.deptno,a.name,b.name from emp as a,emp as b where a.id=b.mgrno;
---------------------------------------------------------
	a.deptno	a.name	b.name	
---------------------------------------------------------
	10	Allen	Tom	
	20	Piter	Boyee	
	30	Jack	Piter	
	30	Jack	Piter	
	10	Tom	Allen	
	20	Harry 	Harry 	
	30	Dick	Jack	
	30	Dick	Jack	
	20	Boyee	Dick	
	30	Jack	Piter	
	30	Jack	Piter	
	20	Piter	Boyee	
	
echo select a.deptno,a.name,b.name from emp as a,emp as b where a.id=b.mgrno group by a.deptno,a.name,b.name;
---------------------------------------------------------
	a.deptno	a.name	b.name	
---------------------------------------------------------
	10	Allen	Tom	
	20	Piter	Boyee	
	30	Jack	Piter	
	10	Tom	Allen	
	20	Harry 	Harry 	
	30	Dick	Jack	
	20	Boyee	Dick	
	
echo select a.deptno,a.name,b.name,count(a.salary),sum(b.salary) from emp as a,emp as b where a.id=b.mgrno group by a.deptno,a.name,b.name;
---------------------------------------------------------
	a.deptno	a.name	b.name	COUNT(a.salary)	SUM(b.salary)	
---------------------------------------------------------
	10	Allen	Tom	1	7000.000000	
	20	Piter	Boyee	2	40000.000000	
	30	Jack	Piter	4	40000.000000	
	10	Tom	Allen	1	10000.000000	
	20	Harry 	Harry 	1	25000.000000	
	30	Dick	Jack	2	18000.000000	
	20	Boyee	Dick	1	15000.000000	
	
echo select a.deptno,a.name,b.name,count(a.salary),sum(b.salary) from emp as a,emp as b where a.id=b.mgrno group by a.deptno,a.name,b.name having count(a.salary)<2 or count(a.salary)>2;
---------------------------------------------------------
	a.deptno	a.name	b.name	COUNT(a.salary)	SUM(b.salary)	
---------------------------------------------------------
	10	Allen	Tom	1	7000.000000	
	30	Jack	Piter	4	40000.000000	
	10	Tom	Allen	1	10000.000000	
	20	Harry 	Harry 	1	25000.000000	
	20	Boyee	Dick	1	15000.000000	
	
echo select a.deptno,a.name,b.name,count(a.salary),sum(b.salary) from emp as a,emp as b where a.id=b.mgrno group by a.deptno,a.name,b.name having (count(a.salary)<2 or count(a.salary)>2) and sum(b.salary)>15000;
---------------------------------------------------------
	a.deptno	a.name	b.name	COUNT(a.salary)	SUM(b.salary)	
---------------------------------------------------------
	30	Jack	Piter	4	40000.000000	
	20	Harry 	Harry 	1	25000.000000	
	
Statement Executed
