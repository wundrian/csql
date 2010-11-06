CREATE TABLE t1 (f1 INT NOT NULL,f2 char(10) NOT NULL,f3 INT);
CREATE INDEX idx on t1 (f1,f2) TREE UNIQUE;
INSERT INTO t1 VALUES(1,'1',1);
INSERT INTO t1 VALUES(3,'1',3);
echo select count(f1) from t1;
select count(f1) from t1;
echo test over
