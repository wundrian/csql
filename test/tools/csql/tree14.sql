create table t1(f1 int not null,f2 int,f3 int);
echo create index idx1 on t1(f1) hash primary;
create index idx1 on t1(f1) hash primary;
echo create index idx2 on t1(f1) tree primary;
create index idx2 on t1(f1) tree primary;

