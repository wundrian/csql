create table t1(f1 int not null,f2 int,f3 int);
create index idx1 on t1(f1) tree;
create index idx2 on t1(f2) tree;
create index idx3 on t1(f3) tree;
create index idx4 on t1(f1,f2) tree;
create index idx5 on t1(f2,f3) tree;
create index idx6 on t1(f3,f1) tree;
create index idx7 on t1(f1,f2,f3) tree;
commit;
