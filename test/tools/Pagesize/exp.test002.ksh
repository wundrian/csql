echo CREATE TABLE t1(f1 int,f2 char(1000));
Statement Executed
echo CREATE TABLE t2(f1 int,f2 char(1000));
Statement Executed
echo CREATE INDEX idx1 ON t2(f1) HASH UNIQUE;
Statement Executed
echo CREATE TABLE t3(f1 int,f2 char(1000));
Statement Executed
echo CREATE INDEX idx2 ON t3(f1) TREE UNIQUE;
Statement Executed
echo CREATE TABLE t4(f1 int,f2 char(1000),PRIMARY KEY(f1));
Statement Executed
echo CREATE TABLE t5(f1 int,f2 int,foreign key(f1) references t4(f1));
Statement Executed
echo CREATE TABLE t6(f1 int,f2 char(1000),PRIMARY KEY(f2));
Statement Executed
echo CREATE TABLE t7(f1 int,f2 char,foreign key(f2) references t6(f2));
Statement Executed
echo CREATE TABLE t8(f1 int,f2 int,f3 char(1000),PRIMARY KEY(f3));
Statement Executed
10000 record inserted
Statement Executed: Rows Affected = 10000
echo DROP TABLE t1;
Statement Executed
echo DROP INDEX idx1;
Statement Executed
echo DROP TABLE t2;
Statement Executed
echo DROP INDEX idx2;
Statement Executed
echo DROP TABLE t3;
Statement Executed
echo DROP TABLE t5;
Statement Executed
echo DROP TABLE t4;
Statement Executed
echo DROP TABLE t7;
Statement Executed
echo DROP TABLE t6;
Statement Executed
echo DROP TABLE t8;
Statement Executed
