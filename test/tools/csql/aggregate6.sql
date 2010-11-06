create table t1 (f1 smallint, f2 bigint, primary key (f1));
insert into t1 values (10, 200);
insert into t1 values (11, 210);
insert into t1 values (20, 500);
insert into t1 values (13, 230);
insert into t1 values (14, 240);
insert into t1 values (50, 500);
insert into t1 values (5, 500);
insert into t1 values (12, 240);
insert into t1 values (11, 210);

echo select * from t1;
select * from t1;
echo select count(*) from t1;
select count(*) from t1;
echo select count(f1) from t1;
select count(f1) from t1;
echo select count(f2) from t1;
select count(f2) from t1;

echo select * from t1 where f1 =11;
select * from t1 where f1 =11;
echo select count(*) from t1 where f1 = 11;
select count(*) from t1 where f1 = 11;
echo select count(f1) from t1 where f1=20;
select count(f1) from t1 where f1=20;
echo select count(f2) from t1 where f2=500;
select count(f2) from t1 where f2=500;

echo select * from t1;
select * from t1;
echo select min(f1) from t1;
select min(f1) from t1;
echo select min(f2) from t1;
select min(f2) from t1;

echo select min(f1) from t1 where f1=20;
select min(f1) from t1 where f1=20;
echo select min(f2) from t1 where f2=500;
select min(f2) from t1 where f2=500;

echo select * from t1;
select * from t1;
echo select max(f1) from t1;
select max(f1) from t1;
echo select max(f2) from t1;
select max(f2) from t1;

echo select max(f1) from t1 where f1=20;
select max(f1) from t1 where f1=20;
echo select max(f2) from t1 where f2=500;
select max(f2) from t1 where f2=500;

echo select * from t1;
select * from t1;
echo select avg(f1) from t1;
select avg(f1) from t1;
echo select avg(f2) from t1;
select avg(f2) from t1;

echo select avg(f1) from t1 where f1=20;
select avg(f1) from t1 where f1=20;
echo select avg(f2) from t1 where f2=500;
select avg(f2) from t1 where f2=500;

echo select * from t1;
select * from t1;
echo select sum(f1) from t1;
select sum(f1) from t1;
echo select sum(f2) from t1;
select sum(f2) from t1;

echo select sum(f1) from t1 where f1=20;
select sum(f1) from t1 where f1=20;
echo select sum(f2) from t1 where f2=500;
select sum(f2) from t1 where f2=500;
echo drop table t1;
drop table t1;
