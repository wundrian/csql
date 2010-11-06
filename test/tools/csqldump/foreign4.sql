CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t2(f3 int,f4 int,primary key(f4),foreign key(f3) references t1(f1));
CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t2(f4));
