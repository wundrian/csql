echo CREATE TABLE t1(f1 int, f2 char(10), f3 date);
Statement Executed
echo CREATE TABLE t2(f1 int, f2 char(10), f3 date);
Statement Executed
echo INSERT INTO t1 VALUES(1, 'ABCD', '2009-08-01');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3, 'BCDA', '2009-08-02');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(5, 'CDBA', '2009-08-03');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(9, 'DCBA', '2009-08-09');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(7, 'ACBD', '2009-08-07');
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(2, 'PQRS', '2009-08-02');
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(3, 'TUVW', '2009-08-03');
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(4, 'EFGH', '2009-08-04');
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(5, 'IJKL', '2009-08-07');
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(6, 'MNOP', '2009-08-08');
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
	
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	2	PQRS	2009/8/2	
	3	TUVW	2009/8/3	
	4	EFGH	2009/8/4	
	5	IJKL	2009/8/7	
	6	MNOP	2009/8/8	
	
echo SELECT * FROM t1,t2;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	2	PQRS	2009/8/2	
	1	ABCD	2009/8/1	3	TUVW	2009/8/3	
	1	ABCD	2009/8/1	4	EFGH	2009/8/4	
	1	ABCD	2009/8/1	5	IJKL	2009/8/7	
	1	ABCD	2009/8/1	6	MNOP	2009/8/8	
	3	BCDA	2009/8/2	2	PQRS	2009/8/2	
	3	BCDA	2009/8/2	3	TUVW	2009/8/3	
	3	BCDA	2009/8/2	4	EFGH	2009/8/4	
	3	BCDA	2009/8/2	5	IJKL	2009/8/7	
	3	BCDA	2009/8/2	6	MNOP	2009/8/8	
	5	CDBA	2009/8/3	2	PQRS	2009/8/2	
	5	CDBA	2009/8/3	3	TUVW	2009/8/3	
	5	CDBA	2009/8/3	4	EFGH	2009/8/4	
	5	CDBA	2009/8/3	5	IJKL	2009/8/7	
	5	CDBA	2009/8/3	6	MNOP	2009/8/8	
	9	DCBA	2009/8/9	2	PQRS	2009/8/2	
	9	DCBA	2009/8/9	3	TUVW	2009/8/3	
	9	DCBA	2009/8/9	4	EFGH	2009/8/4	
	9	DCBA	2009/8/9	5	IJKL	2009/8/7	
	9	DCBA	2009/8/9	6	MNOP	2009/8/8	
	7	ACBD	2009/8/7	2	PQRS	2009/8/2	
	7	ACBD	2009/8/7	3	TUVW	2009/8/3	
	7	ACBD	2009/8/7	4	EFGH	2009/8/4	
	7	ACBD	2009/8/7	5	IJKL	2009/8/7	
	7	ACBD	2009/8/7	6	MNOP	2009/8/8	
	
echo SELECT * FROM t1,t2 LIMIT 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	1	ABCD	2009/8/1	2	PQRS	2009/8/2	
	1	ABCD	2009/8/1	3	TUVW	2009/8/3	
	1	ABCD	2009/8/1	4	EFGH	2009/8/4	
	1	ABCD	2009/8/1	5	IJKL	2009/8/7	
	1	ABCD	2009/8/1	6	MNOP	2009/8/8	
	
echo SELECT * FROM t1,t2 LIMIT 5 OFFSET 5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	3	BCDA	2009/8/2	2	PQRS	2009/8/2	
	3	BCDA	2009/8/2	3	TUVW	2009/8/3	
	3	BCDA	2009/8/2	4	EFGH	2009/8/4	
	3	BCDA	2009/8/2	5	IJKL	2009/8/7	
	3	BCDA	2009/8/2	6	MNOP	2009/8/8	
	
echo SELECT t1.f1, t2.f1 FROM t1 INNER JOIN t2 ON t1.f1 = t2.f1;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	3	3	
	5	5	
	
echo SELECT t1.f1, t2.f1 FROM t1 INNER JOIN t2 ON t1.f1 = t2.f1 LIMIT 2;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	3	3	
	5	5	
	
echo SELECT t1.f1, t2.f1 FROM t1 INNER JOIN t2 ON t1.f1 = t2.f1 LIMIT 2 OFFSET 1;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	5	5	
	
echo SELECT t1.f1, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	1	NULL	
	3	3	
	5	5	
	9	NULL	
	7	NULL	
	
echo SELECT t1.f1, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 LIMIT 4;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	1	NULL	
	3	3	
	5	5	
	9	NULL	
	
echo SELECT t1.f1, t2.f1 FROM t1 LEFT JOIN t2 ON t1.f1 = t2.f1 LIMIT 3 OFFSET 2;
---------------------------------------------------------
	t1.f1	t2.f1	
---------------------------------------------------------
	5	5	
	9	NULL	
	7	NULL	
	
Statement Executed
Statement Executed
