Durablity = TRUE
Server Started
CREATING TABLE
echo CREATE TABLE T1(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T2(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T3(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T4(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T5(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T6(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T7(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T8(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T9(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
echo CREATE TABLE T10(f1 INT,f2 BIGINT,f3 SMALLINT, f4 FLOAT, f5 CHAR(10));
Statement Executed
Server Killed
count=1
Durablity = TRUE
Checking Durability
Server Started
Durability Works Fine
INSERTING INTO TABLE
echo CREATE INDEX idx1 ON T1(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx2 ON T2(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx3 ON T3(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx4 ON T4(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx5 ON T5(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx6 ON T6(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx7 ON T7(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx8 ON T8(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx9 ON T9(f1) UNIQUE;
Statement Executed
echo CREATE INDEX idx10 ON T10(f1) UNIQUE;
Statement Executed
Server Killed
count=2
Durablity = TRUE
Checking Durability
Server Started
Durability Works Fine
INSERTING INTO TABLE
echo INSERT INTO T1 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T1 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T1 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T1 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T1 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T1 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T1 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T1 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T2 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T2 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T3 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T3 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T3 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T4 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T4 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T5 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T5 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T6 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T6 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T7 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T7 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T7 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T8 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T8 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T8 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T9 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T9 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T9 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(1, 10, 101, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T10 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(1, 11, 111, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(1, 11, 101, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(2, 20, 201, 101.101, 'Lakshya');
Statement Executed: Rows Affected = 1
echo INSERT INTO T10 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(2, 21, 211, 101.101, 'LAKSHYA');
Statement execute failed with error -21
echo INSERT INTO T10 VALUES(2, 21, 201, 101.101, 'LAKSHYA');
Statement execute failed with error -21
Server Killed
count=3
Durablity = TRUE
Checking Durability
Server Started
Durability Works Fine
UPDATING RECORDS IN TABLE
echo UPDATE T1 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T1 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T2 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T2 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T3 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T3 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T4 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T4 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T5 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T5 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T6 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T6 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T7 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T7 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T8 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T8 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T9 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T9 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
echo UPDATE T10 SET f4 = 20.02,f5 = 'Jagannath' WHERE f1=2;
Statement Executed: Rows Affected = 1
echo UPDATE T10 SET f1=3 WHERE f1=2;
Statement prepare failed with error -21
Server Killed
count=4
Durablity = TRUE
Checking Durability
Server Started
Durability Works Fine
DELETING RECORDS FROM TABLE
echo DELETE FROM T1 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T2 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T3 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T4 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T5 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T6 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T7 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T8 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T9 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
echo DELETE FROM T10 WHERE f1 = 1;
Statement Executed: Rows Affected = 1
Server Killed
count=5
Durablity = TRUE
Checking Durability
Server Started
Durability Works Fine
DROPPING TABLE
echo DROP TABLE T1;
Statement Executed
echo DROP TABLE T2;
Statement Executed
echo DROP TABLE T3;
Statement Executed
echo DROP TABLE T4;
Statement Executed
echo DROP TABLE T5;
Statement Executed
echo DROP TABLE T6;
Statement Executed
echo DROP TABLE T7;
Statement Executed
echo DROP TABLE T8;
Statement Executed
echo DROP TABLE T9;
Statement Executed
echo DROP TABLE T10;
Statement Executed
