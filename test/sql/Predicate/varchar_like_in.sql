echo CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
INSERT INTO t1 VALUES(1, 'ABCD');
INSERT INTO t1 VALUES(2, 'ABCDE');
INSERT INTO t1 VALUES(3, 'ABCEF');
INSERT INTO t1 VALUES(4, 'ABCCF');
INSERT INTO t1 VALUES(5, 'ABCFF');
INSERT INTO t1 VALUES(6, 'ABCDG');
INSERT INTO t1 VALUES(7, 'ABDCG');
echo select * from t1;
select * from t1;
echo select * from t1 where f2 like 'ABC%';
select * from t1 where f2 like 'ABC%';
echo select * from t1 where f2 like 'ABCD%';
select * from t1 where f2 like 'ABCD%';
echo select * from t1 where f2 like 'ABC%F';
select * from t1 where f2 like 'ABC%F';
echo select * from t1 where f2 like 'ABCD_';
select * from t1 where f2 like 'ABCD_';
echo select * from t1 where f2 in ('ABCDE','ABCCF','ABCDG');
select * from t1 where f2 in ('ABCDE','ABCCF','ABCDG');
echo select * from t1 where f2 in ('ABCDE','ADCBF','ABCDG');
select * from t1 where f2 in ('ABCDE','ADCBF','ABCDG');
echo select * from t1 where f2 in ('ABCDE','ADCBF',NULL);
select * from t1 where f2 in ('ABCDE','ADCBF',NULL);
