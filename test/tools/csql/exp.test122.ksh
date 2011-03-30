echo CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
Statement Executed
echo CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1,f3) references t1(f1,f2));
Statement Executed
echo INSERT INTO t1 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(4,30,300);
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	3	20	100	
	4	30	300	
	
echo INSERT INTO t2 VALUES(1,1000,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(1,1000,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(1,1000,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(4,1000,30);
Statement Executed: Rows Affected = 1
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	1	1000	10	
	1	1000	20	
	1	1000	10	
	4	1000	30	
	
echo UPDATE t2 SET f1=3,f3=20 WHERE f1=1;
Statement Executed: Rows Affected = 3
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f1	t2.f2	t2.f3	
---------------------------------------------------------
	3	1000	20	
	3	1000	20	
	3	1000	20	
	4	1000	30	
	
echo UPDATE t2 SET f3=20 WHERE f1=4;
Statement execute failed with error -34
Statement Executed
Statement Executed
