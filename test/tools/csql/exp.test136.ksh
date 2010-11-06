echo CREATE TABLE t1(f1 INT DEFAULT 5, f2 INT, PRIMARY KEY(f1));
Statement Executed
echo INSERT INTO t1 VALUES(1,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(5,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1(f2) VALUES(10);
Statement execute failed with error -21
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	5	20	
	
Statement Executed
