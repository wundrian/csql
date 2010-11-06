create table t1 ( f1 int, f2 int);
insert into t1 values(1, 1);
insert into t1 values(1, 2);
insert into t1 values(5, 5);
insert into t1 values(2, 1);
insert into t1 values(2, 2);
echo create index ind on t1(f1)unique;
create index ind on t1(f1) unique;
