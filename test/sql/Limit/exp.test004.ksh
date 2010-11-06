echo CREATE TABLE t1(f1 int, f2 char(10), f3 date, f4 BIGINT);
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
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	ABCD	2009/8/1	50	
	3	BCDA	2009/8/2	60	
	5	CDBA	2009/8/3	70	
	3	DCBA	2009/8/9	80	
	4	ACBD	2009/8/7	10	
	1	PQRS	2009/8/2	20	
	2	TUVW	2009/8/3	30	
	3	EFGH	2009/8/4	40	
	4	IJKL	2009/8/7	50	
	5	MNOP	2009/8/8	10	
	4	MMMM	2009/8/2	40	
	3	NNNN	2009/8/3	50	
	2	OOOO	2009/8/4	20	
	1	PPPP	2009/8/7	30	
	2	QQQQ	2009/8/8	50	
	
echo SELECT f1,MAX(f3) FROM t1 GROUP BY f1;
---------------------------------------------------------
	f1	MAX(f3)	
---------------------------------------------------------
	1	2009/8/7	
	3	2009/8/9	
	5	2009/8/8	
	4	2009/8/7	
	2	2009/8/8	
	
echo SELECT f1,COUNT(f3) FROM t1 GROUP BY f1 LIMIT 3;
---------------------------------------------------------
	f1	COUNT(f3)	
---------------------------------------------------------
	1	3	
	3	4	
	5	2	
	
echo SELECT f1,MIN(f3) FROM t1 GROUP BY f1 LIMIT 3 OFFSET 2;
---------------------------------------------------------
	f1	MIN(f3)	
---------------------------------------------------------
	5	2009/8/3	
	4	2009/8/2	
	2	2009/8/3	
	
echo SELECT f1,SUM(f4) FROM t1 GROUP BY f1 LIMIT 3 OFFSET 2;
---------------------------------------------------------
	f1	SUM(f4)	
---------------------------------------------------------
	5	80	
	4	100	
	2	100	
	
Statement Executed
