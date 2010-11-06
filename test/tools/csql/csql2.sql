echo UPDATE and DELETE testing;

create table t1 (f1 int, f2 int, primary key (f1));
insert into t1 values (10, 20);
insert into t1 values (11, 21);
insert into t1 values (12, 22);
insert into t1 values (13, 23);
insert into t1 values (14, 24);
insert into t1 values (50, 50);
echo select * from t1;
select * from t1;
echo select * from t1 where f1 = 100;
select * from t1 where f1 = 50;

echo update t1 set f2 = 100;
update t1 set f2 = 100;
echo select * from t1;
select *  from t1;

echo update t1 set f2 = 200 where f1 =50;
update t1 set f2 =200 where f1 =50;
echo select * from t1;
select *  from t1;

echo delete from t1 where f1 = 50;
delete from t1 where f1 = 50;
echo select * from t1;
select *  from t1;

echo delete from t1;
delete from t1;
echo select * from t1;
select *  from t1;
drop table t1;
