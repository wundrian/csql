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
	
echo SELECT * FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 ORDER BY t1.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t2.f1	t2.f2	t2.f3	t2.f4	
---------------------------------------------------------
	1	DDD	1.600000	2008/7/1	1	DEF	1.500000	2008/7/1	
	1	DEF	1.500000	2008/7/1	1	DEF	1.500000	2008/7/1	
	2	BBB	1.600000	2008/7/4	NULL	NULL	NULL	NULL	
	2	AAA	2.500000	2008/7/1	NULL	NULL	NULL	NULL	
	2	AAA	2.500000	2008/7/2	NULL	NULL	NULL	NULL	
	3	ABB	2.600000	2008/7/5	3	MMM	2.500000	2008/7/3	
	3	AAA	2.500000	2008/7/1	3	MMM	2.500000	2008/7/3	
	4	GGG	4.500000	2008/7/3	4	GGG	4.600000	2008/7/1	
	5	HHH	5.500000	2008/7/3	NULL	NULL	NULL	NULL	
	6	CCC	6.500000	2008/7/4	NULL	NULL	NULL	NULL	
	6	CCC	6.500000	2008/7/2	NULL	NULL	NULL	NULL	
	
echo SELECT t1.f1, t2.f1, t3.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 LEFT JOIN t3 ON t2.f1 = t3.f1 ORDER BY t1.f1;
---------------------------------------------------------
	t1.f1	t2.f1	t3.f1	
---------------------------------------------------------
	1	1	1	
	1	1	1	
	1	1	1	
	1	1	1	
	2	NULL	NULL	
	2	NULL	NULL	
	2	NULL	NULL	
	3	3	NULL	
	3	3	NULL	
	4	4	NULL	
	5	NULL	NULL	
	6	NULL	NULL	
	6	NULL	NULL	
	
echo SELECT * FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 ORDER BY t1.f1,t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t2.f1	t2.f2	t2.f3	t2.f4	
---------------------------------------------------------
	1	DDD	1.600000	2008/7/1	1	DEF	1.500000	2008/7/1	
	1	DEF	1.500000	2008/7/1	1	DEF	1.500000	2008/7/1	
	2	BBB	1.600000	2008/7/4	NULL	NULL	NULL	NULL	
	2	AAA	2.500000	2008/7/1	NULL	NULL	NULL	NULL	
	2	AAA	2.500000	2008/7/2	NULL	NULL	NULL	NULL	
	3	ABB	2.600000	2008/7/5	3	MMM	2.500000	2008/7/3	
	3	AAA	2.500000	2008/7/1	3	MMM	2.500000	2008/7/3	
	4	GGG	4.500000	2008/7/3	4	GGG	4.600000	2008/7/1	
	5	HHH	5.500000	2008/7/3	NULL	NULL	NULL	NULL	
	6	CCC	6.500000	2008/7/4	NULL	NULL	NULL	NULL	
	6	CCC	6.500000	2008/7/2	NULL	NULL	NULL	NULL	
	
echo SELECT t1.f1, t3.f1, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 LEFT JOIN t3 ON t3.f1 = t1.f1 ORDER BY t1.f1,t3.f1,t2.f1;
---------------------------------------------------------
	t1.f1	t3.f1	t2.f1	
---------------------------------------------------------
	1	1	1	
	1	1	1	
	1	1	1	
	1	1	1	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	3	NULL	3	
	3	NULL	3	
	4	NULL	4	
	5	NULL	NULL	
	6	NULL	NULL	
	6	NULL	NULL	
	
echo SELECT t1.f1, t3.f1, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 LEFT JOIN t3 ON t3.f1 = t1.f1 ORDER BY t1.f1 DESC,t3.f1 DESC,t2.f1 DESC;
---------------------------------------------------------
	t1.f1	t3.f1	t2.f1	
---------------------------------------------------------
	6	NULL	NULL	
	6	NULL	NULL	
	5	NULL	NULL	
	4	NULL	4	
	3	NULL	3	
	3	NULL	3	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	2	2	NULL	
	1	1	1	
	1	1	1	
	1	1	1	
	1	1	1	
	
echo SELECT t1.f1, t2.f1, t1.f4, t2.f4 FROM t1 LEFT JOIN t2 ON t1.f1 < 2 OR t1.f3 < 2.5 ORDER BY t1.f4, t2.f4;
---------------------------------------------------------
	t1.f1	t2.f1	t1.f4	t2.f4	
---------------------------------------------------------
	3	NULL	2008/7/1	NULL	
	1	8	2008/7/1	2008/7/1	
	1	9	2008/7/1	2008/7/1	
	1	4	2008/7/1	2008/7/1	
	1	1	2008/7/1	2008/7/1	
	1	8	2008/7/1	2008/7/1	
	1	9	2008/7/1	2008/7/1	
	1	4	2008/7/1	2008/7/1	
	1	1	2008/7/1	2008/7/1	
	1	7	2008/7/1	2008/7/2	
	1	9	2008/7/1	2008/7/2	
	1	7	2008/7/1	2008/7/2	
	1	9	2008/7/1	2008/7/2	
	1	8	2008/7/1	2008/7/3	
	1	3	2008/7/1	2008/7/3	
	1	8	2008/7/1	2008/7/3	
	1	3	2008/7/1	2008/7/3	
	1	9	2008/7/1	2008/7/4	
	1	8	2008/7/1	2008/7/4	
	1	9	2008/7/1	2008/7/4	
	1	8	2008/7/1	2008/7/4	
	1	7	2008/7/1	2008/7/5	
	1	7	2008/7/1	2008/7/5	
	2	NULL	2008/7/1	NULL	
	2	NULL	2008/7/2	NULL	
	6	NULL	2008/7/2	NULL	
	4	NULL	2008/7/3	NULL	
	5	NULL	2008/7/3	NULL	
	2	8	2008/7/4	2008/7/1	
	2	9	2008/7/4	2008/7/1	
	2	4	2008/7/4	2008/7/1	
	2	1	2008/7/4	2008/7/1	
	2	7	2008/7/4	2008/7/2	
	2	9	2008/7/4	2008/7/2	
	2	8	2008/7/4	2008/7/3	
	2	3	2008/7/4	2008/7/3	
	2	9	2008/7/4	2008/7/4	
	2	8	2008/7/4	2008/7/4	
	2	7	2008/7/4	2008/7/5	
	6	NULL	2008/7/4	NULL	
	3	NULL	2008/7/5	NULL	
	
echo SELECT t1.f1, t2.f1, t1.f4, t2.f4 FROM t1 LEFT JOIN t2 ON t1.f1 < 2 OR t1.f3 < 2.5 ORDER BY t1.f1, t1.f4 DESC ;
---------------------------------------------------------
	t1.f1	t2.f1	t1.f4	t2.f4	
---------------------------------------------------------
	1	8	2008/7/1	2008/7/1	
	1	9	2008/7/1	2008/7/4	
	1	7	2008/7/1	2008/7/5	
	1	8	2008/7/1	2008/7/4	
	1	9	2008/7/1	2008/7/1	
	1	8	2008/7/1	2008/7/3	
	1	7	2008/7/1	2008/7/2	
	1	4	2008/7/1	2008/7/1	
	1	3	2008/7/1	2008/7/3	
	1	9	2008/7/1	2008/7/2	
	1	1	2008/7/1	2008/7/1	
	1	8	2008/7/1	2008/7/1	
	1	9	2008/7/1	2008/7/4	
	1	7	2008/7/1	2008/7/5	
	1	8	2008/7/1	2008/7/4	
	1	9	2008/7/1	2008/7/1	
	1	8	2008/7/1	2008/7/3	
	1	7	2008/7/1	2008/7/2	
	1	4	2008/7/1	2008/7/1	
	1	3	2008/7/1	2008/7/3	
	1	9	2008/7/1	2008/7/2	
	1	1	2008/7/1	2008/7/1	
	2	8	2008/7/4	2008/7/1	
	2	9	2008/7/4	2008/7/4	
	2	7	2008/7/4	2008/7/5	
	2	8	2008/7/4	2008/7/4	
	2	9	2008/7/4	2008/7/1	
	2	8	2008/7/4	2008/7/3	
	2	7	2008/7/4	2008/7/2	
	2	4	2008/7/4	2008/7/1	
	2	3	2008/7/4	2008/7/3	
	2	9	2008/7/4	2008/7/2	
	2	1	2008/7/4	2008/7/1	
	2	NULL	2008/7/2	NULL	
	2	NULL	2008/7/1	NULL	
	3	NULL	2008/7/5	NULL	
	3	NULL	2008/7/1	NULL	
	4	NULL	2008/7/3	NULL	
	5	NULL	2008/7/3	NULL	
	6	NULL	2008/7/4	NULL	
	6	NULL	2008/7/2	NULL	
	
echo SELECT t1.f1, t2.f4, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 < 2 OR t2.f1 < 2 ORDER BY t1.f1, t2.f4 ;
---------------------------------------------------------
	t1.f1	t2.f4	t2.f1	
---------------------------------------------------------
	1	2008/7/1	8	
	1	2008/7/1	9	
	1	2008/7/1	4	
	1	2008/7/1	1	
	1	2008/7/1	8	
	1	2008/7/1	9	
	1	2008/7/1	4	
	1	2008/7/1	1	
	1	2008/7/2	7	
	1	2008/7/2	9	
	1	2008/7/2	7	
	1	2008/7/2	9	
	1	2008/7/3	8	
	1	2008/7/3	3	
	1	2008/7/3	8	
	1	2008/7/3	3	
	1	2008/7/4	9	
	1	2008/7/4	8	
	1	2008/7/4	9	
	1	2008/7/4	8	
	1	2008/7/5	7	
	1	2008/7/5	7	
	2	2008/7/1	1	
	2	2008/7/1	1	
	2	2008/7/1	1	
	3	2008/7/1	1	
	3	2008/7/1	1	
	4	2008/7/1	1	
	5	2008/7/1	1	
	6	2008/7/1	1	
	6	2008/7/1	1	
	
echo SELECT t1.f1, t2.f4, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 < 2 OR t2.f1 < 2 ORDER BY t1.f1 DESC, t2.f4 ;
---------------------------------------------------------
	t1.f1	t2.f4	t2.f1	
---------------------------------------------------------
	6	2008/7/1	1	
	6	2008/7/1	1	
	5	2008/7/1	1	
	4	2008/7/1	1	
	3	2008/7/1	1	
	3	2008/7/1	1	
	2	2008/7/1	1	
	2	2008/7/1	1	
	2	2008/7/1	1	
	1	2008/7/1	8	
	1	2008/7/1	9	
	1	2008/7/1	4	
	1	2008/7/1	1	
	1	2008/7/1	8	
	1	2008/7/1	9	
	1	2008/7/1	4	
	1	2008/7/1	1	
	1	2008/7/2	7	
	1	2008/7/2	9	
	1	2008/7/2	7	
	1	2008/7/2	9	
	1	2008/7/3	8	
	1	2008/7/3	3	
	1	2008/7/3	8	
	1	2008/7/3	3	
	1	2008/7/4	9	
	1	2008/7/4	8	
	1	2008/7/4	9	
	1	2008/7/4	8	
	1	2008/7/5	7	
	1	2008/7/5	7	
	
Statement Executed
Statement Executed
Statement Executed
