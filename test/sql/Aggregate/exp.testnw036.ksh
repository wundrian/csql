Network CSql
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo SELECT * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	70	Nihar Pital	NULL	
	2	70	Bijay Sahoo	MGR	
	3	60	Kisor Ambli	Developer	
	2	90	Jiten Lenka	S/W	
	3	80	Papu Paital	NULL	
	4	90	Bhahmananda	MKTING	
	
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo SELECT * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	70	Nihar Pital	NULL	
	2	70	Bijay Sahoo	MGR	
	3	60	Kisor Ambli	Developer	
	2	90	Jiten Lenka	S/W	
	3	80	Papu Paital	NULL	
	4	90	Bhahmananda	MKTING	
	
echo select t1.f1,t1.f2,count(t1.f4),count(t2.f3) from t1,t2 group by t1.f1,t1.f2 ;
---------------------------------------------------------
	t1.f1	t1.f2	COUNT(t1.f4)	COUNT(t2.f3)	
---------------------------------------------------------
	1	70	0	7	
	2	70	7	7	
	3	60	7	7	
	2	90	7	7	
	3	80	0	7	
	4	90	7	7	
	
echo select t1.f1,t1.f2,count(t1.f4),count(t2.f3) from t1,t2 group by t1.f1,t1.f2 having count(t1.f4)<6 and count(t2.f3) >=7;
---------------------------------------------------------
	t1.f1	t1.f2	COUNT(t1.f4)	COUNT(t2.f3)	
---------------------------------------------------------
	1	70	0	7	
	3	80	0	7	
	
echo select t1.f1,t1.f2,count(t1.f3),count(t2.f3) from t1,t2 group by t1.f1,t1.f2 having avg(t1.f2)<70;
---------------------------------------------------------
	t1.f1	t1.f2	COUNT(t1.f3)	COUNT(t2.f3)	
---------------------------------------------------------
	3	60	7	7	
	
Statement Executed
Statement Executed
