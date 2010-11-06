Network CSql
echo CREATE TABLE T1(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT);
Statement Executed
echo INSERT INTO T1 values(100,1);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1(f2) values(10);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1(f2) values(30);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1(f2) values(40);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1(f1,f2) values(NULL,40);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1(f1,f2) values(100,40);
Statement execute failed with error -21
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.f1	T1.f2	
---------------------------------------------------------
	100	1	
	101	10	
	102	30	
	103	40	
	104	40	
	
echo CREATE TABLE T2(f1 SMALLINT AUTO_INCREMENT,f2 CHAR(10));
Statement Executed
echo INSERT INTO T2 values(10,'Papu');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2(f2) values('Jitu');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2(f2) values('kishor');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2(f1,f2) values(NULL,'Nihar');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2(f1,f2) values(100,'Suna');
Statement Executed: Rows Affected = 1
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.f1	T2.f2	
---------------------------------------------------------
	10	Papu	
	11	Jitu	
	12	kishor	
	13	Nihar	
	100	Suna	
	
echo CREATE TABLE T3(f1 CHAR(10),f2 int auto_increment);
Statement Executed
echo INSERT INTO T3 values('Papu',10);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3(f1) values('Jitu');
Statement Executed: Rows Affected = 1
echo INSERT INTO T3(f1) values('kishor');
Statement Executed: Rows Affected = 1
echo INSERT INTO T3(f1,f2) values('Nihar',NULL);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3(f2,f1) values(100,NULL);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3(f1,f2) values(NULL,NULL);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.f1	T3.f2	
---------------------------------------------------------
	Papu	10	
	Jitu	11	
	kishor	12	
	Nihar	13	
	NULL	100	
	NULL	101	
	
echo CREATE TABLE T4(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT);
Statement Executed
echo INSERT INTO T4 VALUES(1,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T4;
---------------------------------------------------------
	T4.f1	T4.f2	
---------------------------------------------------------
	1	2	
	2	2	
	3	3	
	4	2	
	5	3	
	
echo UPDATE T4 SET f2=20 WHERE f2=2;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T4;
---------------------------------------------------------
	T4.f1	T4.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo UPDATE T4 SET f2=200,f1=0 WHERE f2=20;
Statement prepare failed with error -21
echo SELECT * FROM T4;
---------------------------------------------------------
	T4.f1	T4.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo UPDATE T4 SET f2=300,f1=30 WHERE f1<=2;
Statement prepare failed with error -21
echo SELECT * FROM T4;
---------------------------------------------------------
	T4.f1	T4.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo CREATE TABLE T5(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT NOT NULL);
Statement Executed
echo INSERT INTO T5 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(NULL,NULL);
Statement execute failed with error -22
echo INSERT INTO T5 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	1	2	
	3	3	
	4	2	
	5	3	
	
echo DELETE FROM T5 WHERE f2=2;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	3	3	
	5	3	
	
echo ROLLBACK;
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	3	3	
	5	3	
	
echo DELETE FROM T5 WHERE f1<=3 AND f1!=2;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	5	3	
	
echo INSERT INTO T5 VALUES(3,30);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	3	30	
	5	3	
	
echo DELETE FROM T5;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.f1	T5.f2	
---------------------------------------------------------
	
echo CREATE TABLE T6(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT);
Statement Executed
echo INSERT INTO T6 VALUES(1,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(NULL,2);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(NULL,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	2	
	2	2	
	3	3	
	4	2	
	5	3	
	
echo UPDATE T6 SET f2=20 WHERE f2=2;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo UPDATE T6 SET f2=200,f1=0 WHERE f2=20;
Statement prepare failed with error -21
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo UPDATE T6 SET f2=300,f1=30 WHERE f1<=2;
Statement prepare failed with error -21
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo DELETE FROM T6 WHERE f2=2;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo ROLLBACK;
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	1	20	
	2	20	
	3	3	
	4	20	
	5	3	
	
echo DELETE FROM T6 WHERE f1<=3 AND f1!=2;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	2	20	
	4	20	
	5	3	
	
echo INSERT INTO T6 VALUES(3,30);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	3	30	
	2	20	
	4	20	
	5	3	
	
echo DELETE FROM T6;
Statement Executed: Rows Affected = 4
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.f1	T6.f2	
---------------------------------------------------------
	
echo CREATE TABLE T7(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT,f3 SMALLINT);
Statement Executed
echo INSERT INTO T7 VALUES(1,2,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.f1	T7.f2	T7.f3	
---------------------------------------------------------
	1	2	3	
	
echo UPDATE T7 SET f3=30,f2=20,f1=0 where f1=1;
Statement prepare failed with error -21
echo UPDATE T7 SET f3=30,f2=20 where f1=1;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.f1	T7.f2	T7.f3	
---------------------------------------------------------
	1	20	30	
	
echo INSERT INTO T7 VALUES(2,4,3);
Statement Executed: Rows Affected = 1
echo DELETE FROM T7 WHERE f3<=3;
Statement Executed: Rows Affected = 1
echo CREATE TABLE T8(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT,f3 SMALLINT,PRIMARY KEY(f1));
Statement execute failed with error -4
echo INSERT INTO T8 VALUES(1,2,3);
Statement prepare failed with error -5
echo SELECT * FROM T8;
Statement prepare failed with error -5
echo UPDATE T8 SET f3=30,f2=20,f1=0 where f1=1;
Statement prepare failed with error -5
echo UPDATE T8 SET f3=30,f2=20 where f1=1;
Statement prepare failed with error -5
echo SELECT * FROM T8;
Statement prepare failed with error -5
echo INSERT INTO T8 VALUES(2,4,3);
Statement prepare failed with error -5
echo DELETE FROM T8 WHERE f3<=3;
Statement prepare failed with error -5
echo CREATE TABLE T9(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT,f3 SMALLINT);
Statement Executed
echo CREATE INDEX idx1 ON T9(f1,f2) UNIQUE;
Statement Executed
echo INSERT INTO T9 VALUES(1,2,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T9;
---------------------------------------------------------
	T9.f1	T9.f2	T9.f3	
---------------------------------------------------------
	1	2	3	
	
echo UPDATE T9 SET f3=30,f2=20,f1=0 where f1=1;
Statement prepare failed with error -21
echo UPDATE T9 SET f3=30,f2=20 where f1=1;
Statement prepare failed with error -21
echo SELECT * FROM T9;
---------------------------------------------------------
	T9.f1	T9.f2	T9.f3	
---------------------------------------------------------
	1	2	3	
	
echo INSERT INTO T9 VALUES(2,4,3);
Statement Executed: Rows Affected = 1
echo DELETE FROM T9 WHERE f3<=3;
Statement Executed: Rows Affected = 2
echo CREATE TABLE T10(f1 SMALLINT AUTO_INCREMENT,f2 SMALLINT,f3 SMALLINT,PRIMARY KEY(f3,f1));
Statement Executed
echo INSERT INTO T10 VALUES(1,2,3);
Statement Executed: Rows Affected = 1
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.f1	T10.f2	T10.f3	
---------------------------------------------------------
	1	2	3	
	
echo UPDATE T10 SET f3=30,f2=20,f1=0 where f1=1;
Statement prepare failed with error -21
echo UPDATE T10 SET f3=30,f2=20 where f1=1;
Statement prepare failed with error -21
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.f1	T10.f2	T10.f3	
---------------------------------------------------------
	1	2	3	
	
echo INSERT INTO T10 VALUES(2,4,3);
Statement Executed: Rows Affected = 1
echo DELETE FROM T10 WHERE f3<=3;
Statement Executed: Rows Affected = 2
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
