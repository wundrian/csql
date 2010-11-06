echo CREATE TABLE t1(f1 int, f2 char(10), f3 date);
CREATE TABLE t1(f1 int, f2 char(10), f3 date);
INSERT INTO t1 VALUES(1, 'ABCD', '2009-08-01');
INSERT INTO t1 VALUES(3, 'BCDA', '2009-08-02');
INSERT INTO t1 VALUES(5, 'CDBA', '2009-08-03');
INSERT INTO t1 VALUES(9, 'DCBA', '2009-08-09');
INSERT INTO t1 VALUES(7, 'ACBD', '2009-08-07');
INSERT INTO t1 VALUES(2, 'PQRS', '2009-08-02');
INSERT INTO t1 VALUES(3, 'TUVW', '2009-08-03');
INSERT INTO t1 VALUES(4, 'EFGH', '2009-08-04');
INSERT INTO t1 VALUES(5, 'IJKL', '2009-08-07');
INSERT INTO t1 VALUES(6, 'MNOP', '2009-08-08');
INSERT INTO t1 VALUES(2, 'MMMM', '2009-08-02');
INSERT INTO t1 VALUES(3, 'NNNN', '2009-08-03');
INSERT INTO t1 VALUES(4, 'OOOO', '2009-08-04');
INSERT INTO t1 VALUES(5, 'PPPP', '2009-08-07');
INSERT INTO t1 VALUES(6, 'QQQQ', '2009-08-08');
echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t1 ORDER BY f1;
SELECT * FROM t1 ORDER BY f1;
echo SELECT * FROM t1 ORDER BY f1 LIMIT 5;
SELECT * FROM t1 ORDER BY f1 LIMIT 5;
echo SELECT * FROM t1 ORDER BY f1 LIMIT 5 OFFSET 5;
SELECT * FROM t1 ORDER BY f1 LIMIT 5 OFFSET 5;
echo SELECT * FROM t1 ORDER BY f1 DESC;
SELECT * FROM t1 ORDER BY f1 DESC;
echo SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5;
SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5;
echo SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5 OFFSET 5;
SELECT * FROM t1 ORDER BY f1 DESC LIMIT 5 OFFSET 5;
echo SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC;
SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC;
echo SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC LIMIT 5;
SELECT * FROM t1 ORDER BY f1 ASC, f2 DESC LIMIT 5;
echo SELECT * FROM t1 ORDER BY f1 DESC, f2 ASC LIMIT 5 OFFSET 5;
SELECT * FROM t1 ORDER BY f1 DESC, f2 ASC LIMIT 5 OFFSET 5;