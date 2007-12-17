echo create index  test;
create table t1 (f1 integer not null, f2 integer not null, 
                 f3 int not null, f4 int not null,
                 f5 int not null, f6 int not null);
create index idx1 on t1 (f1);
create index idx2 on t1 (f2) UNIQUE;
create index idx3 on t1 (f3) PRIMARY;
create index idx4 on t1 (f4) HASH PRIMARY;
create index idx5 on t1 (f5) TREE;
create index idx6 on t1 (f6) TREE PRIMARY;
drop table t1;
