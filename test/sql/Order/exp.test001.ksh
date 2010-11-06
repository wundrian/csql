Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	98	1	10	AAA	
	99	2	20	BBB	
	100	2	10	CCC	
	101	3	10	AAA	
	102	2	20	BBB	
	
echo select * from t1 order by f2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	98	1	10	AAA	
	102	2	20	BBB	
	100	2	10	CCC	
	99	2	20	BBB	
	101	3	10	AAA	
	
echo select * from t1 order by t1.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	98	1	10	AAA	
	102	2	20	BBB	
	100	2	10	CCC	
	99	2	20	BBB	
	101	3	10	AAA	
	
echo select f2,f3 from t1 order by f2;
---------------------------------------------------------
	f2	f3	
---------------------------------------------------------
	1	10	
	2	20	
	2	10	
	2	20	
	3	10	
	
echo select f4,f2 from t1 order by f4;
---------------------------------------------------------
	f4	f2	
---------------------------------------------------------
	AAA	3	
	AAA	1	
	BBB	2	
	BBB	2	
	CCC	2	
	
Statement Executed
