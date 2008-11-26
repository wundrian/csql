create table t1 ( f1 int, f2 int,f3 int);
insert into t1 values(1,1,1);
insert into t1 values(2,2,2);
insert into t1 values(1,2,3);
echo create index idx1 on t1(f1) tree unique;
create index idx1 on t1(f1) tree unique;
