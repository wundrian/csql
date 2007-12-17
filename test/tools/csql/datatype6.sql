echo double data type testing;

create table t1 (f1 double, f2 double, primary key (f1));
insert into t1 values (0.1073741823, 10.234);
insert into t1 values (-0.1073741823, 11.234);
insert into t1 values (12.234, 11.456);
insert into t1 values (13.123, 11.987);
insert into t1 values (14.467, 12.123);
insert into t1 values (50.345, 10.234);
echo select * from t1;
select * from t1;

echo select * from t1 where f1 BETWEEN 0.1073741822 AND 0.1073741824
select * from t1 where  f1 BETWEEN 0.1073741822 AND 0.1073741824;

echo select * from t1 where f1 BETWEEN -0.1073741824 AND -0.1073741822
select * from t1 where  f1 BETWEEN -0.1073741824 AND -0.1073741822;

echo select * from t1 where f2 < f1;
select * from t1 where f2 < f1;

echo update t1 set f2 = 3.4345 where f2 >11; 
update t1 set f2 = 3.4335 where f2>11;
select * from t1;

echo delete from t1 where f1 > 14.234;
delete from t1 where f1 > 14.234;
select * from t1;
drop table t1;
