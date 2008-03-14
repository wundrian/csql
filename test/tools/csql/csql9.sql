echo Description:BETWEEN and IN test;

create table t1 (f1 int, f2 char(10), f3 int, primary key (f1));
insert into t1 values (10, '20', 10);
insert into t1 values (11, '21', 11);
insert into t1 values (12, '22', 12);
insert into t1 values (13, '23', 13);
insert into t1 values (14, '24', 14);
insert into t1 values (50, '50', 50);
echo  select * from t1 where f1 between 12 and 14;
select * from t1 where f1 between 12 and 14;

echo  select * from t1 where f1 not between 12 and 14;
select * from t1 where f1 not between 12 and 14;

echo  select * from t1 where f3 between 12 and 14;
select * from t1 where f3 between 12 and 14;

echo select * from t1 where f1 IN (12, 14, 50);
echo select * from t1 where f1 IN (12, 14, 50);

echo select * from t1 where f1 IN (12, 14, 50) AND f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) AND f3 IN (50);

echo select * from t1 where f1 IN (12, 14, 50) OR f3 IN (50);
echo select * from t1 where f1 IN (12, 14, 50) OR f3 IN (50);

echo select * from t1 where f1 IN (12, 14, 50) AND f3 between 12 and 14; 
echo select * from t1 where f1 IN (12, 14, 50) AND f3 between 12 and 14;

echo select * from t1 where f1 NOT IN (12, 14, 50);
echo select * from t1 where f1 NOT IN (12, 14, 50);
drop table t1;
