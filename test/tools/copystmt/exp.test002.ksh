echo create table t1(f1 int,f2 char(20));
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo create table ct1 (f1 int, f2 char(20));
Statement Executed
echo create table ct2(f1 int);
Statement Executed
echo create table ct3(f1 char(20));
Statement Executed
echo insert into ct1 as select * from t1;
Statement Executed: Rows Affected = 0
echo insert into ct2 as select f1 from t1;
Statement Executed: Rows Affected = 0
echo insert into ct3 as select f2 from t1;
Statement Executed: Rows Affected = 0
CREATE TABLE t1 (f1 INT , f2 CHAR (20));
CREATE TABLE ct1 (f1 INT , f2 CHAR (20));
CREATE TABLE ct2 (f1 INT );
CREATE TABLE ct3 (f1 CHAR (20));
INSERT INTO t1 VALUES(1, 'CSQL1');
INSERT INTO t1 VALUES(2, 'CSQL2');
INSERT INTO t1 VALUES(3, 'CSQL3');
INSERT INTO t1 VALUES(4, 'CSQL4');
INSERT INTO t1 VALUES(5, 'CSQL5');
INSERT INTO t1 VALUES(6, 'CSQL6');
INSERT INTO t1 VALUES(7, 'CSQL7');
INSERT INTO t1 VALUES(8, 'CSQL8');
INSERT INTO t1 VALUES(9, 'CSQL9');
INSERT INTO t1 VALUES(10, 'CSQL10');
INSERT INTO ct1 VALUES(1, 'CSQL1');
INSERT INTO ct1 VALUES(2, 'CSQL2');
INSERT INTO ct1 VALUES(3, 'CSQL3');
INSERT INTO ct1 VALUES(4, 'CSQL4');
INSERT INTO ct1 VALUES(5, 'CSQL5');
INSERT INTO ct1 VALUES(6, 'CSQL6');
INSERT INTO ct1 VALUES(7, 'CSQL7');
INSERT INTO ct1 VALUES(8, 'CSQL8');
INSERT INTO ct1 VALUES(9, 'CSQL9');
INSERT INTO ct1 VALUES(10, 'CSQL10');
INSERT INTO ct2 VALUES(1);
INSERT INTO ct2 VALUES(2);
INSERT INTO ct2 VALUES(3);
INSERT INTO ct2 VALUES(4);
INSERT INTO ct2 VALUES(5);
INSERT INTO ct2 VALUES(6);
INSERT INTO ct2 VALUES(7);
INSERT INTO ct2 VALUES(8);
INSERT INTO ct2 VALUES(9);
INSERT INTO ct2 VALUES(10);
INSERT INTO ct3 VALUES( 'CSQL1');
INSERT INTO ct3 VALUES( 'CSQL2');
INSERT INTO ct3 VALUES( 'CSQL3');
INSERT INTO ct3 VALUES( 'CSQL4');
INSERT INTO ct3 VALUES( 'CSQL5');
INSERT INTO ct3 VALUES( 'CSQL6');
INSERT INTO ct3 VALUES( 'CSQL7');
INSERT INTO ct3 VALUES( 'CSQL8');
INSERT INTO ct3 VALUES( 'CSQL9');
INSERT INTO ct3 VALUES( 'CSQL10');
Statement Executed
Statement Executed
Statement Executed
Statement Executed
passed
