CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1,f3) references t1(f1,f2));
