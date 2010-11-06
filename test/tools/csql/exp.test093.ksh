echo testing Select Operation Using Primary key
echo CREATE TABLE T4(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F2));
Statement Executed
echo INSERT INTO T4 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T4;
---------------------------------------------------------
	T4.F1	T4.F2	T4.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	20	100	
	
echo SELECT * FROM T4 WHERE F1=1;
---------------------------------------------------------
	T4.F1	T4.F2	T4.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	
echo SELECT * FROM T4 WHERE F1=1 AND F2=20;
---------------------------------------------------------
	T4.F1	T4.F2	T4.F3	
---------------------------------------------------------
	1	20	100	
	
echo SELECT * FROM T4 WHERE F1=1 OR F2=20;
---------------------------------------------------------
	T4.F1	T4.F2	T4.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	
echo testing Updation Operation Using Primary key
echo CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F2));
Statement Executed
echo INSERT INTO T1 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T1 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.F1	T1.F2	T1.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	20	100	
	
echo UPDATE T1 SET F3=200;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.F1	T1.F2	T1.F3	
---------------------------------------------------------
	1	10	200	
	2	10	200	
	1	20	200	
	
echo UPDATE T1 SET F3=100 WHERE F1=1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.F1	T1.F2	T1.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	100	
	
echo UPDATE T1 SET F3=300 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.F1	T1.F2	T1.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	300	
	
echo UPDATE T1 SET F3=100 WHERE F1=1 OR F2=20;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T1;
---------------------------------------------------------
	T1.F1	T1.F2	T1.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	100	
	
echo testing Deletion Operation Using Primary key
echo CREATE TABLE T2(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F2));
Statement Executed
echo INSERT INTO T2 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T2 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T2 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T2 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.F1	T2.F2	T2.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	20	100	
	
echo DELETE FROM T2 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.F1	T2.F2	T2.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	
echo DELETE FROM T2 WHERE F1<=1;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.F1	T2.F2	T2.F3	
---------------------------------------------------------
	2	10	100	
	
echo DELETE FROM T2 WHERE F1<=2;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.F1	T2.F2	T2.F3	
---------------------------------------------------------
	
echo DELETE FROM T2;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T2;
---------------------------------------------------------
	T2.F1	T2.F2	T2.F3	
---------------------------------------------------------
	
echo testing Updation and Deletion Operation Using Primary key
echo CREATE TABLE T3(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F2));
Statement Executed
echo INSERT INTO T3 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T3 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	20	100	
	
echo UPDATE T3 SET F3=200;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	200	
	2	10	200	
	1	20	200	
	
echo UPDATE T3 SET F3=100 WHERE F1=1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	100	
	
echo UPDATE T3 SET F3=300 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	300	
	
echo UPDATE T3 SET F3=100 WHERE F1=1 OR F2=20;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	1	20	100	
	
echo DELETE FROM T3 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	
echo DELETE FROM T3 WHERE F1<=1;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	2	10	200	
	
echo DELETE FROM T3 WHERE F2<=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	
echo DELETE FROM T3;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T3;
---------------------------------------------------------
	T3.F1	T3.F2	T3.F3	
---------------------------------------------------------
	
echo Testing Select Operation Using Primary key
echo CREATE TABLE T5(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F3,F2));
Statement Executed
echo INSERT INTO T5 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T5;
---------------------------------------------------------
	T5.F1	T5.F2	T5.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	1	10	200	
	
echo SELECT * FROM T5 WHERE F3=100;
---------------------------------------------------------
	T5.F1	T5.F2	T5.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	
echo SELECT * FROM T5 WHERE F3=100 AND F2=20;
---------------------------------------------------------
	T5.F1	T5.F2	T5.F3	
---------------------------------------------------------
	1	20	100	
	
echo SELECT * FROM T5 WHERE F2=20 OR F3=100;
---------------------------------------------------------
	T5.F1	T5.F2	T5.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	
echo Testing updation  Operation Using Primary key
echo CREATE TABLE T6(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F3,F2));
Statement Executed
echo INSERT INTO T6 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.F1	T6.F2	T6.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	1	10	200	
	
echo UPDATE T6 SET F1=2;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.F1	T6.F2	T6.F3	
---------------------------------------------------------
	2	10	100	
	2	20	100	
	2	10	200	
	
echo UPDATE T6 SET F1=1 WHERE F3=100;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.F1	T6.F2	T6.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	2	10	200	
	
echo UPDATE T6 SET F1=3 WHERE F3=100 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.F1	T6.F2	T6.F3	
---------------------------------------------------------
	1	10	100	
	3	20	100	
	2	10	200	
	
echo UPDATE T6 SET F1=1 WHERE F2=20 OR F3=100;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T6;
---------------------------------------------------------
	T6.F1	T6.F2	T6.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	2	10	200	
	
echo testing Deletion Operation Using Primary key
echo CREATE TABLE T7(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F3,F2));
Statement Executed
echo INSERT INTO T7 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T7 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T7 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T7 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.F1	T7.F2	T7.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	1	10	200	
	
echo DELETE FROM T7 WHERE F3=100 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.F1	T7.F2	T7.F3	
---------------------------------------------------------
	1	10	100	
	1	10	200	
	
echo DELETE FROM T7 WHERE F3<=100;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.F1	T7.F2	T7.F3	
---------------------------------------------------------
	1	10	200	
	
echo DELETE FROM T7 WHERE F3<=200;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.F1	T7.F2	T7.F3	
---------------------------------------------------------
	
echo DELETE FROM T7;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T7;
---------------------------------------------------------
	T7.F1	T7.F2	T7.F3	
---------------------------------------------------------
	
echo Testing updation And Deletion Operation Using Primary key
echo CREATE TABLE T8(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F3,F2));
Statement Executed
echo INSERT INTO T8 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T8 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T8 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T8 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	1	10	200	
	
echo UPDATE T8 SET F1=2;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	2	10	100	
	2	20	100	
	2	10	200	
	
echo UPDATE T8 SET F1=1 WHERE F3=100;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	2	10	200	
	
echo UPDATE T8 SET F1=3 WHERE F3=100 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	1	10	100	
	3	20	100	
	2	10	200	
	
echo UPDATE T8 SET F1=1 WHERE F2=20 OR F3=100;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	1	10	100	
	1	20	100	
	2	10	200	
	
echo DELETE FROM T8 WHERE F3=100 AND F2=20;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	1	10	100	
	2	10	200	
	
echo DELETE FROM T8 WHERE F3<=100;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	2	10	200	
	
echo DELETE FROM T8 WHERE F3<=200;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	
echo DELETE FROM T8;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T8;
---------------------------------------------------------
	T8.F1	T8.F2	T8.F3	
---------------------------------------------------------
	
echo Testing Select Operation Using Primary key
echo CREATE TABLE T9(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F3));
Statement Executed
echo INSERT INTO T9 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T9 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T9 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T9 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T9;
---------------------------------------------------------
	T9.F1	T9.F2	T9.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo SELECT * FROM T9 WHERE F1=1;
---------------------------------------------------------
	T9.F1	T9.F2	T9.F3	
---------------------------------------------------------
	1	10	100	
	1	10	200	
	
echo SELECT * FROM T9 WHERE F1<=1 AND F2=20;
---------------------------------------------------------
	T9.F1	T9.F2	T9.F3	
---------------------------------------------------------
	
echo SELECT * FROM T9 WHERE F2=20 OR F1=1;
---------------------------------------------------------
	T9.F1	T9.F2	T9.F3	
---------------------------------------------------------
	1	10	100	
	1	10	200	
	
echo Testing updation  Operation Using Primary key
echo CREATE TABLE T10(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F3));
Statement Executed
echo INSERT INTO T10 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T10 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T10 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T10 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.F1	T10.F2	T10.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo UPDATE T10 SET F2=20;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.F1	T10.F2	T10.F3	
---------------------------------------------------------
	1	20	100	
	2	20	100	
	1	20	200	
	
echo UPDATE T10 SET F2=10 WHERE F1=1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.F1	T10.F2	T10.F3	
---------------------------------------------------------
	1	10	100	
	2	20	100	
	1	10	200	
	
echo UPDATE T10 SET F2=30 WHERE F1>=1 AND F3=200;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.F1	T10.F2	T10.F3	
---------------------------------------------------------
	1	10	100	
	2	20	100	
	1	30	200	
	
echo UPDATE T10 SET F2=10 WHERE F2=20 OR F1<=1;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T10;
---------------------------------------------------------
	T10.F1	T10.F2	T10.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo testing Deletion Operation Using Primary key
echo CREATE TABLE T11(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F3));
Statement Executed
echo INSERT INTO T11 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T11 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T11 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T11 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T11;
---------------------------------------------------------
	T11.F1	T11.F2	T11.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo DELETE FROM T11 WHERE F3=100 AND F1=1;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T11;
---------------------------------------------------------
	T11.F1	T11.F2	T11.F3	
---------------------------------------------------------
	2	10	100	
	1	10	200	
	
echo DELETE FROM T11 WHERE F1<=1;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T11;
---------------------------------------------------------
	T11.F1	T11.F2	T11.F3	
---------------------------------------------------------
	2	10	100	
	
echo DELETE FROM T11 WHERE F3<=200;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T11;
---------------------------------------------------------
	T11.F1	T11.F2	T11.F3	
---------------------------------------------------------
	
echo DELETE FROM T11;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T11;
---------------------------------------------------------
	T11.F1	T11.F2	T11.F3	
---------------------------------------------------------
	
echo Testing updation And Deletion Operation Using Primary key
echo CREATE TABLE T12(F1 INT,F2 SMALLINT,F3 BIGINT,PRIMARY KEY(F1,F3));
Statement Executed
echo INSERT INTO T12 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T12 VALUES(2,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO T12 VALUES(1,10,200);
Statement Executed: Rows Affected = 1
echo INSERT INTO T12 VALUES(1,10,100);
Statement execute failed with error -21
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo UPDATE T12 SET F2=20;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	20	100	
	2	20	100	
	1	20	200	
	
echo UPDATE T12 SET F2=10 WHERE F1=1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	10	100	
	2	20	100	
	1	10	200	
	
echo UPDATE T12 SET F2=30 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	10	100	
	2	20	100	
	1	10	200	
	
echo UPDATE T12 SET F2=10 WHERE F2<=20 OR F1=1;
Statement Executed: Rows Affected = 3
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo DELETE FROM T12 WHERE F1=1 AND F2=20;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	1	10	100	
	2	10	100	
	1	10	200	
	
echo DELETE FROM T12 WHERE F1<=1;
Statement Executed: Rows Affected = 2
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	2	10	100	
	
echo DELETE FROM T12 WHERE F1>=2;
Statement Executed: Rows Affected = 1
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	
echo DELETE FROM T12;
Statement Executed: Rows Affected = 0
echo SELECT * FROM T12;
---------------------------------------------------------
	T12.F1	T12.F2	T12.F3	
---------------------------------------------------------
	
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
Statement Executed
