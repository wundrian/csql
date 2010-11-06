Network CSql
echo create table T1 ( f1 int, f2 bigint, f3 smallint,f4 tinyint);
Statement Executed
echo create index idx1 on T1(f1) unique;
Statement Executed
echo create index idx2 on T1(f2) unique;
Statement Executed
echo create index idx3 on T1(f3) unique;
Statement Executed
echo create index idx4 on T1(f4) unique;
Statement Executed
echo create index idx5 on T1(f1,f1) unique;
Statement execute failed with error -4
echo create index idx6 on T1(f1,f2) unique;
Statement Executed
echo create index idx7 on T1(f1,f3) unique;
Statement Executed
echo create index idx8 on T1(f1,f4) unique;
Statement Executed
echo create index idx9 on T1(f2,f1) unique;
Statement execute failed with error -4
echo create index idx10 on T1(f2,f2) unique;
Statement execute failed with error -4
echo create index idx11 on T1(f2,f3) unique;
Statement Executed
echo create index idx12 on T1(f2,f4) unique;
Statement Executed
echo create index idx13 on T1(f3,f1) unique;
Statement execute failed with error -4
echo create index idx14 on T1(f3,f2) unique;
Statement execute failed with error -4
echo create index idx15 on T1(f3,f3) unique;
Statement execute failed with error -4
echo create index idx16 on T1(f3,f4) unique;
Statement Executed
echo create index idx17 on T1(f4,f1) unique;
Statement execute failed with error -4
echo create index idx18 on T1(f4,f2) unique;
Statement execute failed with error -4
echo create index idx19 on T1(f4,f3) unique;
Statement execute failed with error -4
echo create index idx20 on T1(f4,f4) unique;
Statement execute failed with error -4
echo create index idx21 on T1(f1,f2,f3) unique;
Statement Executed
echo create index idx22 on T1(f1,f2,f4) unique;
Statement Executed
echo create index idx23 on T1(f1,f3,f2) unique;
Statement execute failed with error -4
echo create index idx24 on T1(f1,f3,f4) unique;
Statement Executed
echo create index idx25 on T1(f1,f4,f1) unique;
Statement execute failed with error -4
echo create index idx26 on T1(f1,f4,f3) unique;
Statement execute failed with error -4
echo create index idx27 on T1(f2,f1,f3) unique;
Statement execute failed with error -4
echo create index idx28 on T1(f2,f1,f4) unique;
Statement execute failed with error -4
echo create index idx29 on T1(f2,f3,f1) unique;
Statement execute failed with error -4
echo create index idx30 on T1(f2,f3,f4) unique;
Statement Executed
echo create index idx31 on T1(f2,f4,f1) unique;
Statement execute failed with error -4
echo create index idx32 on T1(f2,f4,f3) unique;
Statement execute failed with error -4
echo create index idx33 on T1(f3,f1,f2) unique;
Statement execute failed with error -4
echo create index idx34 on T1(f3,f1,f4) unique;
Statement execute failed with error -4
echo create index idx35 on T1(f3,f1,f2) unique;
Statement execute failed with error -4
echo create index idx36 on T1(f3,f1,f4) unique;
Statement execute failed with error -4
echo create index idx37 on T1(f3,f2,f1) unique;
Statement execute failed with error -4
echo create index idx38 on T1(f3,f2,f4) unique;
Statement execute failed with error -4
echo create index idx39 on T1(f4,f2,f1) unique;
Statement execute failed with error -4
echo create index idx40 on T1(f4,f2,f3) unique;
Statement execute failed with error -4
echo create index idx41 on T1(f4,f3,f1) unique;
Statement execute failed with error -4
echo create index idx42 on T1(f4,f3,f2) unique;
Statement execute failed with error -4
echo create index idx43 on T1(f4,f1,f2) unique;
Statement execute failed with error -4
echo create index idx44 on T1(f4,f1,f3) unique;
Statement execute failed with error -4
echo create index idx45 on T1(f1,f2,f3,f4) unique;
Statement Executed
echo create index idx46 on T1(f2,f1,f4,f3) unique;
Statement execute failed with error -4
echo create index idx47 on T1(f1,f4,f3,f2) unique;
Statement execute failed with error -4
echo create index idx48 on T1(f4,f3,f1,f2) unique;
Statement execute failed with error -4
echo "Tree Index";
echo create index idx01 on T1(f1) tree unique;
Statement Executed
echo create index idx02 on T1(f2) tree unique;
Statement Executed
echo create index idx03 on T1(f3) tree unique;
Statement Executed
echo create index idx04 on T1(f4) tree unique;
Statement Executed
echo create index idx05 on T1(f1,f1) tree unique;
Statement execute failed with error -14
echo create index idx06 on T1(f1,f2) tree unique;
Statement execute failed with error -14
echo create index idx07 on T1(f1,f3) tree unique;
Statement execute failed with error -14
echo create index idx08 on T1(f1,f4) tree unique;
Statement execute failed with error -14
echo create index idx09 on T1(f2,f1) tree unique;
Statement execute failed with error -14
echo DROP TABLE T1;
Statement Executed
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo "Hash Index";
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -4
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -4
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -4
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -4
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -4
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
echo "Tree Index";
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -21
Statement execute failed with error -14
Statement execute failed with error -14
Statement execute failed with error -14
Statement execute failed with error -14
Statement execute failed with error -14
CREATE TABLE t1 (f1 INT , f2 BIGINT , f3 SMALLINT , f4 TINYINT );
INSERT INTO t1 VALUES(1,2,3,4);
INSERT INTO t1 VALUES(1,3,5,6);
INSERT INTO t1 VALUES(1,3,7,8);
INSERT INTO t1 VALUES(1,3,7,8);
Network CSql
Statement Executed
