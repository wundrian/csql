echo CREATE TABLE t1(f1 SMALLINT DEFAULT NULL, f2 INT DEFAULT NULL, f3 BIGINT DEFAULT NULL, f4 TINYINT DEFAULT NULL, f5 CHAR(15) DEFAULT NULL, f6 FLOAT DEFAULT NULL, f7 DOUBLE DEFAULT NULL, f8 DATE DEFAULT NULL, f9 TIME DEFAULT NULL, f10 TIMESTAMP); 
CREATE TABLE t1(f1 SMALLINT DEFAULT NULL, f2 INT DEFAULT NULL, f3 BIGINT DEFAULT NULL, f4 TINYINT DEFAULT NULL, f5 CHAR(15) DEFAULT NULL, f6 FLOAT DEFAULT NULL, f7 DOUBLE DEFAULT NULL, f8 DATE DEFAULT NULL, f9 TIME DEFAULT NULL, f10 TIMESTAMP); 
echo INSERT INTO t1(f10) VALUES('2009-07-19 05:37:01');
INSERT INTO t1(f10) VALUES('2009-07-19 05:37:01');
echo INSERT INTO t1 VALUES(1, 1234, 12345678, 45, 'CSQL', 1.23, 12345.6789, '2009/10/01', '12:34:56', '2009-07-19 05:37:01');
INSERT INTO t1 VALUES(1, 1234, 12345678, 45, 'CSQL', 1.23, 12345.6789, '2009/10/01', '12:34:56', '2009-07-19 05:37:01');

echo SELECT * FROM t1;
SELECT * FROM t1;