echo CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
Statement Executed
echo CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1,f3) references t1(f1,f2));
Statement Executed
echo INSERT INTO t1 VALUES(1,10,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(1,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(2,20,100);
Statement Executed: Rows Affected = 1
echo INSERT INTO t1 VALUES(3,30,300);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(1,1000,10);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(1,1000,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(2,1000,20);
Statement Executed: Rows Affected = 1
echo INSERT INTO t2 VALUES(3,1000,30);
Statement Executed: Rows Affected = 1
echo DELETE FROM t1 WHERE f1=1;
Statement execute failed with error -36
Statement Executed
Statement Executed
