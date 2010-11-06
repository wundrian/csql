create table t1(f1 int,f2 char(20),primary key(f1));
insert into t1 values(1,'Hi');
insert into t1 values(2,'Hello');
insert into t1 values(3,'Hi All');
commit;
create table t2(f1 int,f2 char(20),primary key(f1));
insert into t2 values(10,'mysql');
insert into t2 values(20,'open');
insert into t2 values(30,'source');
commit;

