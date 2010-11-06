echo CREATE TABLE t1(f1 int,f2 int,f3 char(15));
Statement Executed
echo INSERT INTO t1 VALUES(1,70,'Nihar Pital');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,70,'Bijay Sahoo');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,60,'Kisor Ambli');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,90,'Jiten Lenka');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,80,'Papu Paital');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1,80,'Bijay Sahoo');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,70,'Jiten Lenka');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1,70,'Bijay Sahoo');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,70,'Bijay Sahoo');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,60,'Papu Paital');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1,70,'Nihar Pital');
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	70	Nihar Pital	
	2	70	Bijay Sahoo	
	3	60	Kisor Ambli	
	2	91	Jiten Lenka	
	3	81	Papu Paital	
	1	80	Bijay Sahoo	
	2	70	Jiten Lenka	
	1	72	Bijay Sahoo	
	2	70	Bijay Sahoo	
	3	60	Papu Paital	
	1	71	Nihar Pital	
	
echo SELECT f1,sum(f2),count(f2),avg(f2),min(f2),max(f2),count(f3) from t1 GROUP BY f1 having sum(f2) >300 ;
---------------------------------------------------------
	f1	SUM(f2)	COUNT(f2)	AVG(f2)	MIN(f2)	MAX(f2)	COUNT(f3)	
---------------------------------------------------------
	2	301	4	75.250000	70	91	4	
	
echo SELECT f3,count(f1),sum(f2),count(f2),avg(f2),min(f2),max(f2) from t1 GROUP BY f3 having avg(f2) <75;
---------------------------------------------------------
	f3	COUNT(f1)	SUM(f2)	COUNT(f2)	AVG(f2)	MIN(f2)	MAX(f2)	
---------------------------------------------------------
	Nihar Pital	2	141	2	70.500000	70	71	
	Bijay Sahoo	4	292	4	73.000000	70	80	
	Kisor Ambli	1	60	1	60.000000	60	60	
	Papu Paital	2	141	2	70.500000	60	81	
	
echo SELECT f1,sum(f2),count(f2),avg(f2),min(f2),max(f2) from t1 GROUP BY f1;
---------------------------------------------------------
	f1	SUM(f2)	COUNT(f2)	AVG(f2)	MIN(f2)	MAX(f2)	
---------------------------------------------------------
	1	293	4	73.250000	70	80	
	2	301	4	75.250000	70	91	
	3	201	3	67.000000	60	81	
	
echo SELECT f1,sum(f2),count(f2),avg(f2),min(f2),max(f2) from t1 GROUP BY f1 having avg(f2) <70 or min(f2)=70;
---------------------------------------------------------
	f1	SUM(f2)	COUNT(f2)	AVG(f2)	MIN(f2)	MAX(f2)	
---------------------------------------------------------
	1	293	4	73.250000	70	80	
	2	301	4	75.250000	70	91	
	3	201	3	67.000000	60	81	
	
Statement Executed
