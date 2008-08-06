Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo create index ind on t1(f1)unique;
Statement Executed
CREATE TABLE t1 (f1 INT , f2 INT );
CREATE INDEX ind on t1 (  f1  )  UNIQUE;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1,1);
INSERT INTO t1 VALUES(1,2);
INSERT INTO t1 VALUES(5,5);
INSERT INTO t1 VALUES(2,1);
INSERT INTO t1 VALUES(2,2);
COMMIT;
Statement Executed

wrong expected file test failed
