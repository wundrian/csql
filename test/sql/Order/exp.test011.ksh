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
	
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	t2.f4	
---------------------------------------------------------
	1	DEF	1.500000	2008/7/1	
	9	QQQ	9.500000	2008/7/2	
	3	MMM	2.500000	2008/7/3	
	4	GGG	4.600000	2008/7/1	
	7	PPP	7.500000	2008/7/2	
	8	NNN	8.500000	2008/7/3	
	9	QQQ	9.500000	2008/7/1	
	8	AAA	8.500000	2008/7/4	
	7	AAA	7.500000	2008/7/5	
	9	BBB	9.800000	2008/7/4	
	8	EEE	8.800000	2008/7/1	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f1	t3.f2	t3.f3	t3.f4	
---------------------------------------------------------
	1	DEF	1.500000	2008/7/1	
	2	AAA	2.500000	2008/7/2	
	7	PPP	7.500000	2008/7/3	
	8	NNN	8.500000	2008/7/4	
	9	QQQ	9.500000	2008/7/1	
	10	NNN	10.500000	2008/7/2	
	1	DEF	1.500000	2008/7/3	
	2	AAA	2.500000	2008/7/4	
	7	PPP	7.500000	2008/7/1	
	8	NNN	8.500000	2008/7/2	
	10	NNN	10.500000	2008/7/4	
	
echo SELECT t1.f1, t2.f1, SUM(t1.f3) FROM t1 INNER JOIN t2 ON t1.f1=t2.f1 AND t1.f1 IN(1,2,4,5,6) AND t2.f1 BETWEEN 2 AND 6 LEFT JOIN t3 ON t2.f1 != 5 WHERE t1.f1 <= t2.f1 OR t2.f2 >=2 AND (t2.f3 LIKE 'A%' OR t2.f3 LIKE 'B%' OR t2.f3 LIKE 'Q%') GROUP BY t1.f1, t2.f1 HAVING SUM(t1.f3) >1 ORDER BY t1.f1;


	
echo SELECT t1.f1, t2.f1, t3.f1, SUM(t1.f3) FROM t1 INNER JOIN t2 ON t1.f1=t2.f1 AND t1.f1 IN(1,2,4,5,6) OR t2.f1 BETWEEN 2 AND 6 LEFT JOIN t3 ON t2.f1 != 5 WHERE t1.f1 <= t2.f1 OR t2.f2 >=2 OR t2.f3 LIKE 'A%' OR t2.f3 LIKE 'B%' OR t2.f3 LIKE 'Q%' GROUP BY t1.f1, t2.f1, t3.f1 HAVING SUM(t1.f3) >1 ORDER BY t1.f1;


	
echo SELECT t1.f1, t2.f1, t3.f1, SUM(t1.f3) FROM t1 INNER JOIN t2 ON t1.f1=t2.f1 AND t1.f1 IN(1,2,4,5,6) AND t2.f1 BETWEEN 2 AND 6 LEFT JOIN t3 ON t2.f1 != 5 WHERE t1.f1 <= t2.f1 OR t2.f2 >=2 AND (t2.f3 LIKE 'A%' OR t2.f3 LIKE 'B%' OR t2.f3 LIKE 'Q%') GROUP BY t1.f1, t2.f1, t3.f1 HAVING SUM(t1.f3) >1 ORDER BY t1.f1;

For the above 3 queries retrieved records are more than expected records. Just verify it
	
Statement Executed
Statement Executed
Statement Executed


