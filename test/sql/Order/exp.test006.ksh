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
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	3	AAA	2.500000	2008/7/1	
	2	AAA	2.500000	2008/7/2	
	4	GGG	4.500000	2008/7/3	
	1	DEF	1.500000	2008/7/1	
	6	CCC	6.500000	2008/7/2	
	5	HHH	5.500000	2008/7/3	
	2	AAA	2.500000	2008/7/1	
	6	CCC	6.500000	2008/7/4	
	3	ABB	2.600000	2008/7/5	
	2	BBB	1.600000	2008/7/4	
	1	DDD	1.600000	2008/7/1	
	
echo SELECT f1, f2, SUM(f3) FROM t1 GROUP BY f1, f2 ORDER BY f1;
---------------------------------------------------------
	f1	f2	SUM(f3)	
---------------------------------------------------------
	1	DDD	1.600000	
	1	DEF	1.500000	
	2	BBB	1.600000	
	2	AAA	5.000000	
	3	ABB	2.600000	
	3	AAA	2.500000	
	4	GGG	4.500000	
	5	HHH	5.500000	
	6	CCC	13.000000	
	
echo SELECT f1, f2, SUM(f3), COUNT(f4) FROM t1 GROUP BY f1, f2 ORDER BY f1, f2;
---------------------------------------------------------
	f1	f2	SUM(f3)	COUNT(f4)	
---------------------------------------------------------
	1	DDD	1.600000	1	
	1	DEF	1.500000	1	
	2	AAA	5.000000	2	
	2	BBB	1.600000	1	
	3	AAA	2.500000	1	
	3	ABB	2.600000	1	
	4	GGG	4.500000	1	
	5	HHH	5.500000	1	
	6	CCC	13.000000	2	
	
echo SELECT f1, SUM(f3), MIN(f2), MAX(f4) FROM t1 GROUP BY f1 ORDER BY f1;
---------------------------------------------------------
	f1	SUM(f3)	MIN(f2)	MAX(f4)	
---------------------------------------------------------
	1	3.100000	DDD	2008/7/1	
	2	6.600000	AAA	2008/7/4	
	3	5.100000	AAA	2008/7/5	
	4	4.500000	GGG	2008/7/3	
	5	5.500000	HHH	2008/7/3	
	6	13.000000	CCC	2008/7/4	
	
echo SELECT f1, SUM(f3), MIN(f2), MAX(f4) FROM t1 GROUP BY f1 HAVING SUM(f3) <= 5.5 ORDER BY f1;
---------------------------------------------------------
	f1	SUM(f3)	MIN(f2)	MAX(f4)	
---------------------------------------------------------
	1	3.100000	DDD	2008/7/1	
	3	5.100000	AAA	2008/7/5	
	4	4.500000	GGG	2008/7/3	
	5	5.500000	HHH	2008/7/3	
	
Statement Executed
