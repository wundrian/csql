echo create table t1(f1 char(10),f2 char(10),f3 int);
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
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	s	y	5000	
	p	q	4000	
	z	y	2000	
	p	y	3000	
	c	q	1000	
	z	y	1500	
	s	y	3000	
	c	t	2500	
	s	p	2300	
	c	q	4000	
	c	y	5000	
	c	p	3500	
	
echo select f2,avg(f3) from t1 group by f2;
---------------------------------------------------------
	f2	AVG(f3)	
---------------------------------------------------------
	y	3250.000000	
	q	3000.000000	
	t	2500.000000	
	p	2900.000000	
	
echo select f2,avg(f3) from t1 where f3>=3000 group by f2 ;
---------------------------------------------------------
	f2	AVG(f3)	
---------------------------------------------------------
	y	4000.000000	
	q	4000.000000	
	p	3500.000000	
	
echo select f2,avg(f3) from t1 where f3>=2000 group by f2 having avg(f3)>3000;
---------------------------------------------------------
	f2	AVG(f3)	
---------------------------------------------------------
	y	3600.000000	
	q	4000.000000	
	
echo select f2,avg(f3) from t1 where f3>=2000 group by f2 having avg(f3)>3000 limit 1;
---------------------------------------------------------
	f2	AVG(f3)	
---------------------------------------------------------
	y	3600.000000	
	
echo select f2,avg(f3) from t1 where f3>=2000 or f2 = 'y' group by f2 having avg(f3)>3000;
---------------------------------------------------------
	f2	AVG(f3)	
---------------------------------------------------------
	y	3250.000000	
	q	4000.000000	
	
echo select f1,f2,avg(f3) from t1 where f3>=2000 or f2 = 'y' group by f1,f2 having avg(f3)>3000 ;
---------------------------------------------------------
	f1	f2	AVG(f3)	
---------------------------------------------------------
	s	y	4000.000000	
	p	q	4000.000000	
	c	q	4000.000000	
	c	y	5000.000000	
	c	p	3500.000000	
	
echo select f2,f1,avg(f3) from t1 where f3>=2000 or f2 = 'y' group by f1,f2 having avg(f3)>3000;
---------------------------------------------------------
	f2	f1	AVG(f3)	
---------------------------------------------------------
	y	s	4000.000000	
	q	p	4000.000000	
	q	c	4000.000000	
	y	c	5000.000000	
	p	c	3500.000000	
	
echo select f2,f1,avg(f3) from t1 where f3>=2000 or f2 = 'y' group by f1,f2 having avg(f3)>2000 ;
---------------------------------------------------------
	f2	f1	AVG(f3)	
---------------------------------------------------------
	y	s	4000.000000	
	q	p	4000.000000	
	y	p	3000.000000	
	t	c	2500.000000	
	p	s	2300.000000	
	q	c	4000.000000	
	y	c	5000.000000	
	p	c	3500.000000	
	
echo select f2,f1,avg(f3) from t1 where f3>=2000 or f2 = 'y' group by f1,f2 having avg(f3)>2000 limit 3 offset 2;
---------------------------------------------------------
	f2	f1	AVG(f3)	
---------------------------------------------------------
	y	p	3000.000000	
	t	c	2500.000000	
	p	s	2300.000000	
	
Statement Executed
