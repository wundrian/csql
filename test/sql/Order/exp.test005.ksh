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
	
echo SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	DDD	1.600000	2008/7/1	
	1	DEF	1.500000	2008/7/1	
	2	BBB	1.600000	2008/7/4	
	2	AAA	2.500000	2008/7/1	
	2	AAA	2.500000	2008/7/2	
	3	ABB	2.600000	2008/7/5	
	3	AAA	2.500000	2008/7/1	
	4	GGG	4.500000	2008/7/3	
	
echo SELECT * FROM t1 WHERE f1 <= 4 ORDER BY f1 DESC;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	4	GGG	4.500000	2008/7/3	
	3	ABB	2.600000	2008/7/5	
	3	AAA	2.500000	2008/7/1	
	2	BBB	1.600000	2008/7/4	
	2	AAA	2.500000	2008/7/1	
	2	AAA	2.500000	2008/7/2	
	1	DDD	1.600000	2008/7/1	
	1	DEF	1.500000	2008/7/1	
	
echo SELECT f1, t1.f2, f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4;
---------------------------------------------------------
	f1	t1.f2	f4	
---------------------------------------------------------
	1	DDD	2008/7/1	
	1	DEF	2008/7/1	
	2	AAA	2008/7/1	
	2	AAA	2008/7/2	
	2	BBB	2008/7/4	
	3	AAA	2008/7/1	
	3	ABB	2008/7/5	
	4	GGG	2008/7/3	
	
echo SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4 DESC;
---------------------------------------------------------
	f1	f2	t1.f4	
---------------------------------------------------------
	1	DDD	2008/7/1	
	1	DEF	2008/7/1	
	2	BBB	2008/7/4	
	2	AAA	2008/7/2	
	2	AAA	2008/7/1	
	3	ABB	2008/7/5	
	3	AAA	2008/7/1	
	4	GGG	2008/7/3	
	
echo SELECT f1, f2, t1.f4 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC;
---------------------------------------------------------
	f1	f2	t1.f4	
---------------------------------------------------------
	4	GGG	2008/7/3	
	3	ABB	2008/7/5	
	3	AAA	2008/7/1	
	2	BBB	2008/7/4	
	2	AAA	2008/7/2	
	2	AAA	2008/7/1	
	1	DDD	2008/7/1	
	1	DEF	2008/7/1	
	
echo SELECT f1, t1.f4, f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY t1.f1, f4, t1.f2;
---------------------------------------------------------
	f1	t1.f4	f2	
---------------------------------------------------------
	1	2008/7/1	DDD	
	1	2008/7/1	DEF	
	2	2008/7/1	AAA	
	2	2008/7/2	AAA	
	2	2008/7/4	BBB	
	3	2008/7/1	AAA	
	3	2008/7/5	ABB	
	4	2008/7/3	GGG	
	
echo SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1, t1.f4, f2 DESC;
---------------------------------------------------------
	t1.f1	f4	t1.f2	
---------------------------------------------------------
	1	2008/7/1	DEF	
	1	2008/7/1	DDD	
	2	2008/7/1	AAA	
	2	2008/7/2	AAA	
	2	2008/7/4	BBB	
	3	2008/7/1	AAA	
	3	2008/7/5	ABB	
	4	2008/7/3	GGG	
	
echo SELECT t1.f1, f4, t1.f2 FROM t1 WHERE t1.f1 <= 4 OR t1.f3 <= 4.5 ORDER BY f1 DESC, t1.f4 DESC, f2 DESC;
---------------------------------------------------------
	t1.f1	f4	t1.f2	
---------------------------------------------------------
	4	2008/7/3	GGG	
	3	2008/7/5	ABB	
	3	2008/7/1	AAA	
	2	2008/7/4	BBB	
	2	2008/7/2	AAA	
	1	2008/7/1	DEF	
	2	2008/7/1	AAA	
	1	2008/7/1	DDD	
	
Statement Executed
