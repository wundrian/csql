Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement execute failed with error -21
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select count(f1) from t1;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	6	
	
echo select * from t1 where f1=1 and f2=1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	1	1	1	
	
echo select * from t1 where f1=5 and f2=1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=5;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	5	2	5	
	
echo select * from t1 where f1=7;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
echo select * from t1 where f1=10 and f2=2 and f3=10;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	10	2	10	
	
echo select * from t1 where f1=10 and f2=6 and f3=10;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	
CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  NOT NULL , f3 INT );
CREATE INDEX t1_idx1_Primary on t1 (  f1  ,f2  )  HASH  UNIQUE;
INSERT INTO t1 VALUES(1,1,1);
INSERT INTO t1 VALUES(2,1,2);
INSERT INTO t1 VALUES(3,1,3);
INSERT INTO t1 VALUES(5,2,5);
INSERT INTO t1 VALUES(10,2,10);
INSERT INTO t1 VALUES(100,3,100);
Statement Executed
