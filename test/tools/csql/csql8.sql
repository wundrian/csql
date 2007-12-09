echo Description:count(*) test

create table t1 (f1 int, f2 int, primary key (f1));
insert into t1 values (10, 20);
insert into t1 values (11, 21);
insert into t1 values (12, 22);
insert into t1 values (13, 23);
insert into t1 values (14, 24);
insert into t1 values (50, 50);
echo select * from t1;
select count(*) from t1;
echo select * from t1 where f1 =11;
select count(*) from t1 where f1 = 11;
