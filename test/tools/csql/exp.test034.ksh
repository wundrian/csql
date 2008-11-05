Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1 where f1 = 5;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	5	5	
	
echo create index ind on t1(f1);
Statement Executed
echo select * from t1 where f1 = 5;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	5	5	
	
CREATE TABLE t1 (f1 INT , f2 INT );
CREATE INDEX ind on t1 (  f1  )  HASH ;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1,1);
INSERT INTO t1 VALUES(1,2);
INSERT INTO t1 VALUES(5,5);
INSERT INTO t1 VALUES(2,1);
INSERT INTO t1 VALUES(2,2);
COMMIT;
Statement Executed
