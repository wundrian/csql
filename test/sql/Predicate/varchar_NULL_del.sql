echo CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
INSERT INTO t1 VALUES(1, 'ABCD');
INSERT INTO t1 VALUES(2, 'NULL');
INSERT INTO t1 VALUES(3, NULL);
INSERT INTO t1 VALUES(4, 'ABCEF');
INSERT INTO t1 (f1) VALUES (5);
INSERT INTO t1 VALUES(6, 'ABCFF');
echo select * from t1;
select * from t1;
echo DELETE FROM t1 where f2 IS NOT NULL;
DELETE FROM t1 where f2 IS NOT NULL;
echo select * from t1;
select * from t1;
echo DELETE FROM t1 where f2 IS NULL;
DELETE FROM t1 where f2 IS NULL;
echo select * from t1;
select * from t1;
