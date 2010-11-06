echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t1(f1 int,f2 int,primary key(f1));
echo CREATE TABLE t2(f3 int,f4 int,primary key(f4),foreign key(f3) references t1(f1));
CREATE TABLE t2(f3 int,f4 int,primary key(f4),foreign key(f3) references t1(f1));
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t2(f4));
CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t2(f4));
echo INSERT INTO t1 values(1,10);
INSERT INTO t1 values(1,10);
echo INSERT INTO t1 values(2,20);
INSERT INTO t1 values(2,20);

echo INSERT INTO t2 values(1,100);
INSERT INTO t2 values(1,100);
echo INSERT INTO t2 values(1,200);
INSERT INTO t2 values(1,200);
echo INSERT INTO t2 values(2,300);
INSERT INTO t2 values(2,300);

echo INSERT INTO t3 values(100,1000);
INSERT INTO t3 values(100,1000);
echo INSERT INTO t3 values(100,1000);
INSERT INTO t3 values(100,1000);
echo INSERT INTO t3 values(200,1000);
INSERT INTO t3 values(200,1000);
echo INSERT INTO t3 values(200,1000);
INSERT INTO t3 values(200,1000);

echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo SELECT * FROM t3;
SELECT * FROM t3;

echo INSERT INTO t2 values(3,100);
INSERT INTO t2 values(3,100);

echo INSERT INTO t3 values(400,1000);
INSERT INTO t3 values(400,1000);

echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo SELECT * FROM t3;
SELECT * FROM t3;

echo UPDATE t3 SET f5=400 where f5=200; 
UPDATE t3 SET f5=400 where f5=200; 
echo UPDATE t1 SET f1=3 where f1=2; 
UPDATE t1 SET f1=3 where f1=2; 
echo UPDATE t2 SET f4=400 where f5=200; 
UPDATE t2 SET f4=400 where f5=200; 

echo UPDATE t3 SET f5=300 where f5=200; 
UPDATE t3 SET f5=300 where f5=200; 

echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo SELECT * FROM t3;
SELECT * FROM t3;

echo DELETE FROM t1 WHERE f1=2;
DELETE FROM t1 WHERE f1=2;
echo DELETE FROM t2 where f4=200;
DELETE FROM t2 where f4=200;

echo DELETE FROM t3 WHERE f5=300;
DELETE FROM t3 WHERE f5=300;
echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo SELECT * FROM t3;
SELECT * FROM t3;
echo DELETE FROM t2 where f4 IN(200,300,400);
DELETE FROM t2 where f4 IN(200,300,400);
echo DELETE FROM t1 WHERE f1=2;
DELETE FROM t1 WHERE f1=2;

echo SELECT * FROM t1;
SELECT * FROM t1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo SELECT * FROM t3;
SELECT * FROM t3;

