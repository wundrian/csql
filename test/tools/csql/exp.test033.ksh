Statement Executed
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select count(f1) from t1;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	2	
	
CREATE TABLE t1 (f1 INT  NOT NULL , f2 CHAR (12) NOT NULL , f3 INT );
CREATE INDEX idx on t1 (  f1  ,f2  )  TREE  UNIQUE;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1, '1',1);
INSERT INTO t1 VALUES(3, '1',3);
COMMIT;
Statement Executed
