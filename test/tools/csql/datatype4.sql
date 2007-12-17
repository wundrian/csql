echo bit data type testing;

create table t1 (f1 bit, f2 bit));
insert into t1 values (0, 0);
insert into t1 values (1, 1);
insert into t1 values (0, 1);
insert into t1 values (1, 0);
echo select * from t1;
select * from t1;
echo select * from t1 where f1 = 1;
select * from t1 where f1 = 1;
echo select * from t1 where f1 = 1 AND f1 = 1;
select * from t1 where f1 = 1 AND f1 = 1;
echo select * from t1 where f1 != 0 AND f2 != 0 ;
select * from t1 where f1 != 0 AND f2 !=0 
echo select * from t1 where f1 = 12 AND f2 >= 22;
select * from t1 where f1 = 12 AND f2 >= 22;

echo select * from t1 where NOT f1 = 1;
select * from t1 where NOT f1 = 1;
echo select * from t1 where f1 != 1;
select * from t1 where f1 != 1;
echo select * from t1 where NOT f1 != 1;
select * from t1 where NOT f1 != 1;

echo select * from t1 where f1 = f2;
select * from t1 where f1 = f2;

echo update t1 set f2 = 1 where f1 != f2;
update t1 set f2 = 1 where f1 != f2;
select * from t1;

echo update t1 set f2 = 0 where f1 = 1;
update t1 set f2 = 0 where f1 = 1;
select * from t1;

delete from t1 where f1 = 1;
select * from t1;
drop table t1;
