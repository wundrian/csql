echo CREATE TABLE t1(f1 int, f2 char(10), f3 date);
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
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	
	3	BCDA	2009/8/2	
	5	CDBA	2009/8/3	
	9	DCBA	2009/8/9	
	7	ACBD	2009/8/7	
	2	PQRS	2009/8/2	
	3	TUVW	2009/8/3	
	4	EFGH	2009/8/4	
	5	IJKL	2009/8/7	
	6	MNOP	2009/8/8	
	2	MMMM	2009/8/2	
	3	NNNN	2009/8/3	
	4	OOOO	2009/8/4	
	5	PPPP	2009/8/7	
	6	QQQQ	2009/8/8	
	
echo SELECT * FROM t1 ORDER BY f1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	
	2	MMMM	2009/8/2	
	2	PQRS	2009/8/2	
	3	NNNN	2009/8/3	
	3	TUVW	2009/8/3	
	3	BCDA	2009/8/2	
	4	OOOO	2009/8/4	
	4	EFGH	2009/8/4	
	5	PPPP	2009/8/7	
	5	IJKL	2009/8/7	
	5	CDBA	2009/8/3	
	6	QQQQ	2009/8/8	
	6	MNOP	2009/8/8	
	7	ACBD	2009/8/7	
	9	DCBA	2009/8/9	
	
echo SELECT * FROM t1 ORDER BY f1 LIMIT 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	
	2	MMMM	2009/8/2	
	2	PQRS	2009/8/2	
	3	NNNN	2009/8/3	
	3	TUVW	2009/8/3	
	
echo SELECT * FROM t1 ORDER BY f1 LIMIT 5 OFFSET 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	3	BCDA	2009/8/2	
	4	OOOO	2009/8/4	
	4	EFGH	2009/8/4	
	5	PPPP	2009/8/7	
	5	IJKL	2009/8/7	
	
echo SELECT * FROM t1 ORDER BY f1 DESC;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	9	DCBA	2009/8/9	
	7	ACBD	2009/8/7	
	6	QQQQ	2009/8/8	
	6	MNOP	2009/8/8	
	5	PPPP	2009/8/7	
	5	IJKL	2009/8/7	
	5	CDBA	2009/8/3	
	4	OOOO	2009/8/4	
	4	EFGH	2009/8/4	
	3	NNNN	2009/8/3	
	3	TUVW	2009/8/3	
	3	BCDA	2009/8/2	
	2	MMMM	2009/8/2	
	2	PQRS	2009/8/2	
	1	ABCD	2009/8/1	
	
echo SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	9	DCBA	2009/8/9	
	7	ACBD	2009/8/7	
	6	QQQQ	2009/8/8	
	6	MNOP	2009/8/8	
	5	PPPP	2009/8/7	
	
echo SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5 OFFSET 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	5	IJKL	2009/8/7	
	5	CDBA	2009/8/3	
	4	OOOO	2009/8/4	
	4	EFGH	2009/8/4	
	3	NNNN	2009/8/3	
	
echo SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	
	2	PQRS	2009/8/2	
	2	MMMM	2009/8/2	
	3	TUVW	2009/8/3	
	3	NNNN	2009/8/3	
	3	BCDA	2009/8/2	
	4	OOOO	2009/8/4	
	4	EFGH	2009/8/4	
	5	PPPP	2009/8/7	
	5	IJKL	2009/8/7	
	5	CDBA	2009/8/3	
	6	QQQQ	2009/8/8	
	6	MNOP	2009/8/8	
	7	ACBD	2009/8/7	
	9	DCBA	2009/8/9	
	
echo SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC LIMIT 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	
	2	PQRS	2009/8/2	
	2	MMMM	2009/8/2	
	3	TUVW	2009/8/3	
	3	NNNN	2009/8/3	
	
echo SELECT * FROM t1 ORDER BY f1 DESC, f2 ASC LIMIT 5 OFFSET 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	5	IJKL	2009/8/7	
	5	PPPP	2009/8/7	
	4	EFGH	2009/8/4	
	4	OOOO	2009/8/4	
	3	BCDA	2009/8/2	
	
Statement Executed
