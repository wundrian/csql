Statement prepare failed with error -19
Statement Executed
echo CREATE TABLE t2(f3 int,f4 int,primary key(f3));
Statement Executed
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3));
Statement Executed
echo DROP TABLE t2;
Statement execute failed with error -4
Statement Executed
Statement Executed
Statement Executed
