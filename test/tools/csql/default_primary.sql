echo CREATE TABLE t1(f1 INT DEFAULT 5, f2 INT, PRIMARY KEY(f1));
CREATE TABLE t1(f1 INT DEFAULT 5, f2 INT, PRIMARY KEY(f1));
echo INSERT INTO t1 VALUES(1,10);
INSERT INTO t1 VALUES(1,10);
echo INSERT INTO t1 VALUES(5,20);
INSERT INTO t1 VALUES(5,20);
echo INSERT INTO t1(f2) VALUES(10); 
INSERT INTO t1(f2) VALUES(10); 
echo SELECT * FROM t1;
SELECT * FROM t1;
