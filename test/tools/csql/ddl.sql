
create table t1 (f1 int, f2 int);
insert into t1 values (10, 20);
insert into t1 (f1, f2) values (11, 21);
insert into t1 (f2, f1) values (22, 12);
insert into t1 (f1) values (13);
insert into t1 (f2) values (24);
select * from t1;
