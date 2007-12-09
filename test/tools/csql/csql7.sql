echo Descr:drop index  test
create table t1 (f1 integer not null, f2 integer not null, 
                 f3 int not null, f4 int not null);
create index idx1 on t1 (f1);
create index idx2 on t1 (f2) UNIQUE;
create index idx3 on t1 (f3) PRIMARY;
drop index idx2;
