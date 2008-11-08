echo create tree index test;
create table t1 ( f1 int not null, f2 int);
create index idx on t1(f1) tree unique;
insert into t1 values(1,2);
insert into t1 values(1,2);




