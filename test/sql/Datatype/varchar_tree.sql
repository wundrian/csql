echo create table t1 (f1 varchar(10), f2 smallint);
create table t1 (f1 varchar(10), f2 smallint);
echo create table t2 (f1 varchar(10), f2 smallint);
create table t2 (f1 varchar(10), f2 smallint);
echo create index idx1 on t1(f1) tree;
create index idx1 on t1(f1) tree;
echo create index idx2 on t2(f1) tree unique;
create index idx2 on t2(f1) tree unique;
