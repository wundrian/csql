CREATE TABLE t1(f1 INT,f2 INT, PRIMARY KEY(f1));
INSERT INTO t1 VALUES(3,10);
INSERT INTO t1 VALUES(1,20);
INSERT INTO t1 VALUES(2,20);
CREATE TABLE t2(f1 INT,f2 INT,FOREIGN KEY(f1) REFERENCES t1(f1));
INSERT INTO t2 VALUES(1,10);
INSERT INTO t2 VALUES(2,20);
INSERT INTO t2 VALUES(2,10);
INSERT INTO t2 VALUES(1,20);
DELETE FROM t1 WHERE f1=1;

