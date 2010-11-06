create table t1(f1 int,f2 int,f3 int);
insert into t1 values(98, 1, 10);
insert into t1 values(99, NULL, 20);
insert into t1 values(100, 3, 30);
insert into t1 values(101, 4, NULL);
insert into t1 values(102, 5, 50);
create table t2(f1 int,f2 int,f3 int);
insert into t2 values(98, 1, 10);
insert into t2 values(99, 2, 20);
insert into t2 values(100, NULL, NULL);
insert into t2 values(101, 4, 40);
insert into t2 values(102, NULL, 50);
select * from t1;
select * from t2;

