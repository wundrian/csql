echo create table t1(f1 int,f2 int);
create table t1(f1 int,f2 int);
echo create index idx1 on t1(f1) tree;
create index idx1 on t1(f1) tree;
echo create table t2(f1 int,f2 int);
create table t2(f1 int,f2 int);
echo create index idx2 on t2(f2,f1) hash;
create index idx2 on t2(f2,f1) hash;
