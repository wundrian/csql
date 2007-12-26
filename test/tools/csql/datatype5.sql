echo float data type testing;
create table t1 (f1 float, f2 float);
insert into t1 values (0.1048575, 10.234);
insert into t1 values (-0.1048575, 11.234);
insert into t1 values (12.234, 11.456);
insert into t1 values (13.123, 11.987);
insert into t1 values (14.467, 12.123);
insert into t1 values (50.345, 10.234);
insert into t1 values (123.456E3, 10.234);
insert into t1 values (123456E-3, 10.234);
echo select * from t1;
select * from t1;

echo select * from t1 where f1 BETWEEN 0.104856 AND 0.104858
select * from t1 where  f1 BETWEEN 0.104856 AND 0.104858;

echo select * from t1 where f1 >122 AND f1 <124;
select * from t1 where  f1 >122 AND f1 <124;

echo select * from t1 where f1 BETWEEN -0.104859 AND -0.104856
select * from t1 where  f1 BETWEEN -0.104859 AND -0.104856;

echo select * from t1 where f1 BETWEEN -124 AND -122
select * from t1 where  f1 BETWEEN  -124 AND -122;

echo select * from t1 where f2 < f1;
select * from t1 where f2 < f1;

echo update t1 set f2 = 3.4345 where f2 >11; 
update t1 set f2 = 3.4335 where f2>11;
select * from t1;

echo delete from t1 where f1 > 14.234;
delete from t1 where f1 > 14.234;
select * from t1;
drop table t1;
