echo CREATE TABLE t1(f1 int, f2 CHAR(10), f3 FLOAT, f4 TIMESTAMP);
Statement Executed
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
	1	NULL	7.500000	2009/7/29 1:1:1.0	
	NULL	NULL	NULL	2009/7/29 1:1:1.0	
	10	PAPU	NULL	2009/7/29 1:1:1.0	
	20	NULL	7.500000	2009/7/29 1:1:1.0	
	NULL	PAPU	7.500000	2009/7/29 1:1:1.0	
	30	PAPU	7.500000	2009/7/29 1:1:1.0	
	
echo SELECT * FROM t1 WHERE f1 IS NULL;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	NULL	NULL	NULL	2009/7/29 1:1:1.0	
	NULL	PAPU	7.500000	2009/7/29 1:1:1.0	
	
echo UPDATE t1 SET f2 = 'MUNA' WHERE f1 IS NULL;
Statement Executed: Rows Affected = 2
echo UPDATE t1 SET f2 = 'RAHUL' WHERE f1 IS NOT NULL;
Statement Executed: Rows Affected = 4
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	1	RAHUL	7.500000	2009/7/29 1:1:1.0	
	NULL	MUNA	NULL	2009/7/29 1:1:1.0	
	10	RAHUL	NULL	2009/7/29 1:1:1.0	
	20	RAHUL	7.500000	2009/7/29 1:1:1.0	
	NULL	MUNA	7.500000	2009/7/29 1:1:1.0	
	30	RAHUL	7.500000	2009/7/29 1:1:1.0	
	
echo SELECT * FROM t1 WHERE f2 IS NULL;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	
echo UPDATE t1 SET f1 = 1000 WHERE f2 IS NULL;
Statement Executed: Rows Affected = 0
echo UPDATE t1 SET f1 = 2000 ,f2 = 'MONA' WHERE f2 IS NOT NULL;
Statement Executed: Rows Affected = 6
echo UPDATE t1 SET f1 = 3000 ,f2 = 'TIMA' WHERE f2 IS NULL;
Statement Executed: Rows Affected = 0
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	2000	MONA	7.500000	2009/7/29 1:1:1.0	
	2000	MONA	NULL	2009/7/29 1:1:1.0	
	2000	MONA	NULL	2009/7/29 1:1:1.0	
	2000	MONA	7.500000	2009/7/29 1:1:1.0	
	2000	MONA	7.500000	2009/7/29 1:1:1.0	
	2000	MONA	7.500000	2009/7/29 1:1:1.0	
	
echo SELECT * FROM t1 WHERE f3 IS NULL;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	2000	MONA	NULL	2009/7/29 1:1:1.0	
	2000	MONA	NULL	2009/7/29 1:1:1.0	
	
echo UPDATE t1 SET f3 = 5.7 WHERE f3 IS NULL;
Statement Executed: Rows Affected = 2
echo UPDATE t1 SET f3 = 6.7 WHERE f3 IS NOT NULL;
Statement Executed: Rows Affected = 6
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	
echo DELETE FROM t1 WHERE f1 IS NULL;
Statement Executed: Rows Affected = 0
echo DELETE FROM t1 WHERE f2 IS NULL;
Statement Executed: Rows Affected = 0
echo DELETE FROM t1 WHERE f3 IS NULL;
Statement Executed: Rows Affected = 0
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	2000	MONA	6.700000	2009/7/29 1:1:1.0	
	
echo DELETE FROM t1 WHERE f1 IS NOT NULL;
Statement Executed: Rows Affected = 6
echo DELETE FROM t1 WHERE f2 IS NOT NULL;
Statement Executed: Rows Affected = 0
echo DELETE FROM t1 WHERE f3 IS NOT NULL;
Statement Executed: Rows Affected = 0
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	
---------------------------------------------------------
	
Statement Executed
