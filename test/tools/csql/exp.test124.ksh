echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
Statement Executed
echo CREATE TABLE t2(f3 int,f4 int,primary key(f3));
Statement Executed
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3) );
Statement Executed
echo INSERT INTO t1 values(1,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 values(2,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 values(3,30);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 values(4,40);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(1,3);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(1,4);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(2,3);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(2,4);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(2,4);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(1,5);
Statement execute failed with error -35
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	2	20	
	
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f3	t2.f4	
---------------------------------------------------------
	3	30	
	4	40	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	1	3	
	1	4	
	2	3	
	2	4	
	2	4	
	
echo DELETE FROM t3;
Statement Executed: Rows Affected = 5
echo DELETE FROM t2;
Statement Executed: Rows Affected = 2
echo DELETE FROM t1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f3	t2.f4	
---------------------------------------------------------
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	
Statement Executed
Statement Executed
Statement Executed
