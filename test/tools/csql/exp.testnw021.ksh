Network CSql
Statement Executed
Statement execute failed with error -14
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select count(f1) from t1;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	2	
	
CREATE TABLE t1 (f1 INT  NOT NULL , f2 CHAR (10) NOT NULL , f3 INT );
INSERT INTO t1 VALUES(1, '1',1);
INSERT INTO t1 VALUES(3, '1',3);
Network CSql
Statement Executed
