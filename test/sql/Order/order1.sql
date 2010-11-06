create table t1(f1 int,f2 int,f3 int,f4 char(10),primary key(f1));
insert into t1 values(98,1,10,'AAA');
insert into t1 values(99,2,20,'BBB');
insert into t1 values(100,2,10,'CCC'); 
insert into t1 values(101,3,10,'AAA'); 
insert into t1 values(102,2,20,'BBB');

echo select * from t1;
select * from t1;

echo select * from t1 order by f2;
select * from t1 order by f2;

echo select * from t1 order by t1.f2;
select * from t1 order by t1.f2;

echo select f2,f3 from t1 order by f2;
select f2,f3 from t1 order by f2;

echo select f4,f2 from t1 order by f4;
select f4,f2 from t1 order by f4;
