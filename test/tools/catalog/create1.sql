echo create table t2 and constraints with three integer fields and primary key f1;
create table t2 (f1 int,f2 int,f3 int,primary key(f1));
create index t2Uniqueidx on t2(f3) unique;
