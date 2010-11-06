echo CREATE TABLE t1(f1 int,f2 int,primary key(f1));
CREATE TABLE t1(f1 int,f2 int,primary key(f1));
echo CREATE TABLE t2(f3 int,f4 int,primary key(f3));
CREATE TABLE t2(f3 int,f4 int,primary key(f3));
echo CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3) );
CREATE TABLE t3(f5 int,f6 int,foreign key(f5) references t1(f1),foreign key(f6) references t2(f3) );
