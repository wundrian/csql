CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t2(f1 int,f2 int,foreign key(f1) references t1(f1));
