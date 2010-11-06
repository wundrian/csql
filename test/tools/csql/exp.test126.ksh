echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
Statement Executed
echo CREATE TABLE t2(f1 int NOT NULL,f2 int,foreign key(f1) references t1(f1));
Statement Executed
echo CREATE INDEX idx1 on t2(f1) Hash Unique;
Statement Executed
echo INSERT INTO t1 VALUES(1,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(1,10);
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	
	
echo INSERT INTO t2 VALUES(1,20);
Statement execute failed with error -21
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	1	10	
	
Statement Executed
Statement Executed
