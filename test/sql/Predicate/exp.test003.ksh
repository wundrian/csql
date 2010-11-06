echo CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
Statement Executed
echo INSERT INTO t1 VALUES(1, 'ABCD');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2, 'NULL');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3, NULL);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(4, 'ABCEF');
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 (f1) VALUES (5);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(6, 'ABCFF');
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	NULL	
	3	NULL	
	4	ABCEF	
	5	NULL	
	6	ABCFF	
	
echo select * from t1 where f2 is null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3	NULL	
	5	NULL	
	
echo select * from t1 where f2 is not null;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	ABCD	
	2	NULL	
	4	ABCEF	
	6	ABCFF	
	
Statement Executed
