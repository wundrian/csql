echo create table t1 (f1 int, f2 char(10), f3 bigint);
create table t1 (f1 int, f2 char(10), f3 bigint);

echo insert into t1 values(10,'india',1234321); 
insert into t1 values(10,'india',1234321); 
echo insert into t1 (f1, f2 ) values(20,'INDIA'); 
insert into t1 (f1, f2 ) values(20,'INDIA'); 
echo insert into t1 (f2, f3 ) values('orissa',123432); 
insert into t1 (f2, f3 ) values('orissa',123432); 
echo insert into t1 (f1, f3 ) values(30,123432); 
insert into t1 (f1, f3 ) values(30,123432); 

echo select * from t1;
select * from t1;
echo select f1,f2,f3 from t1;
select f1,f2,f3 from t1;
echo select f2,f1,f3 from t1;
select f2,f1,f3 from t1;
echo select f1,f1,f1,f1,f1 from t1;
select f1,f1,f1,f1,f1 from t1;
echo select f2,f2,f2,f2,f2 from t1;
select f2,f2,f2,f2,f2 from t1;
echo select f3,f3,f3,f3,f3 from t1;
select f3,f3,f3,f3,f3 from t1;
echo select f1,f1,f2,f2,f3,f3 from t1;
select f1,f1,f2,f2,f3,f3 from t1;
echo select f1,f2,f1,f3,f3,f2,f1,f3 from t1;
select f1,f2,f1,f3,f3,f2,f1,f3 from t1;

echo drop table t1;
drop table t1;

