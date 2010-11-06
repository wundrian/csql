echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
Statement Executed
echo CREATE TABLE t2(f3 int,f4 int,primary key(f3));
Statement Executed
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3) );
Statement Executed
Statement Executed
Statement Executed
Statement Executed
