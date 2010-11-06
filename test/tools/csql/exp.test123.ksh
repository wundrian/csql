echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
Statement Executed
echo CREATE TABLE t2(f3 int,f4 int,primary key(f4),foreign key(f3) references t1(f1));
Statement Executed
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t2(f4));
Statement Executed
echo INSERT INTO t1 values(1,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 values(2,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 values(1,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 values(1,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 values(2,300);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(100,1000);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(100,1000);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(200,1000);
Statement Executed: Rows Affected = 1
echo INSERT INTO t3 values(200,1000);
Statement Executed: Rows Affected = 1
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
	1	100	
	1	200	
	2	300	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	100	1000	
	100	1000	
	200	1000	
	200	1000	
	
echo INSERT INTO t2 values(3,100);
Statement execute failed with error -35
echo INSERT INTO t3 values(400,1000);
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
	1	100	
	1	200	
	2	300	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	100	1000	
	100	1000	
	200	1000	
	200	1000	
	
echo UPDATE t3 SET f5=400 where f5=200;
Statement execute failed with error -35
echo UPDATE t1 SET f1=3 where f1=2;
Statement prepare failed with error -21
echo UPDATE t2 SET f4=400 where f5=200;
Statement prepare failed with error -21
echo UPDATE t3 SET f5=300 where f5=200;
Statement Executed: Rows Affected = 2
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
	1	100	
	1	200	
	2	300	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	100	1000	
	100	1000	
	300	1000	
	300	1000	
	
echo DELETE FROM t1 WHERE f1=2;
Statement execute failed with error -36
echo DELETE FROM t2 where f4=200;
Statement Executed: Rows Affected = 1
echo DELETE FROM t3 WHERE f5=300;
Statement Executed: Rows Affected = 2
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
	1	100	
	2	300	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	100	1000	
	100	1000	
	
echo DELETE FROM t2 where f4 IN(200,300,400);
Statement Executed: Rows Affected = 1
echo DELETE FROM t1 WHERE f1=2;
Statement Executed: Rows Affected = 1
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	10	
	
echo SELECT * FROM t2;
---------------------------------------------------------
	t2.f3	t2.f4	
---------------------------------------------------------
	1	100	
	
echo SELECT * FROM t3;
---------------------------------------------------------
	t3.f5	t3.f6	
---------------------------------------------------------
	100	1000	
	100	1000	
	
Statement Executed
Statement Executed
Statement Executed
