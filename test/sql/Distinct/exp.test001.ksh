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
	99	2	20	BBB	
	
echo select distinct * from t1 ;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	98	1	10	AAA	
	99	2	20	BBB	
	100	2	10	CCC	
	101	3	10	AAA	
	
echo select distinct f2 from t1 ;
---------------------------------------------------------
	f2	
---------------------------------------------------------
	1	
	2	
	3	
	
echo select distinct f4 from t1 ;
---------------------------------------------------------
	f4	
---------------------------------------------------------
	AAA	
	BBB	
	CCC	
	
echo select distinct f2, f4 from t1 ;
---------------------------------------------------------
	f2	f4	
---------------------------------------------------------
	1	AAA	
	2	BBB	
	2	CCC	
	3	AAA	
	
Statement Executed
