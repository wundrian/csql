CREATE TABLE t1 (f1 SMALLINT , f2 INT );
CREATE INDEX t1_PRIMARY on t1 ( f1 ) ;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1,1111);
INSERT INTO t1 VALUES(2,2222);
COMMIT;
CREATE TABLE t1 (f1 SMALLINT , f2 INT );
CREATE INDEX t1_PRIMARY on t1 ( f1 ) ;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1,1111);
INSERT INTO t1 VALUES(2,2222);
INSERT INTO t1 VALUES(5,5555);
INSERT INTO t1 VALUES(6,6666);
COMMIT;