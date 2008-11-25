create table t1(f1 int not null,f2 int,f3 int);
create index idx1 on t1(f1,f2) tree;
commit;
