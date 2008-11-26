create table t1(f1 int not null,f2 int,f3 int,primary key(f1));
echo create index idx1 on t1(f1) unique;
create index idx1 on t1(f1) unique;

