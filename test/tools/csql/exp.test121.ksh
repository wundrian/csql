echo CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
Statement Executed
echo CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1) references t1(f1));
Statement execute failed with error -4
Statement Executed
Statement Executed
