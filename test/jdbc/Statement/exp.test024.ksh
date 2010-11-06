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
echo Select f1,f5 from T1 order by f1;
---------------------------------------------------------
	f1	f5	
---------------------------------------------------------
	100	6000.000000	
	100	4000.000000	
	100	1000.000000	
	200	7000.000000	
	200	5000.000000	
	200	2000.000000	
	300	8000.000000	
	300	3000.000000	
	400	5000.000000	
	1000	9000.000000	
	
SELECT T1.f1,AVG(T1.f5) FROM T1 GROUP BY T1.f1;
T1.f1	AVG(T1.f5)
100	3666.6666666666665
200	4666.666666666667
300	5500.0
400	5000.0
1000	9000.0
SELECT f1,AVG(f5) FROM T1 GROUP BY f1 HAVING AVG(f5)>5000;
T1.f1	AVG(T1.f5)
300	5500.0
1000	9000.0
SELECT f1,AVG(f5) FROM T1 WHERE f1>200 GROUP BY f1;
T1.f1	AVG(T1.f5)
300	5500.0
400	5000.0
1000	9000.0
SELECT f1,AVG(f5) FROM T1 WHERE f1> 100 GROUP BY f1 HAVING AVG(f5)>5000;
T1.f1	T1.f2	AVG(T1.f5)
300	5500.0
1000	9000.0
