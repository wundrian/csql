create table t1(f1 int not null,f2 int,f3 int);
echo create index idx1 on t1(f1) unique;
create index idx1 on t1(f1) unique;
echo create index idx2 on t1(f1) primary;
create index idx2 on t1(f1) primary;
echo create index idx3 on t1(f1) hash primary;
create index idx3 on t1(f1) hash primary;

