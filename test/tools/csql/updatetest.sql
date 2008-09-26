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

echo update t1 set f1=10;
update t1 set f1=10;
echo select * from t1;
select * from t1;
echo update t1 set f2='hello';
update t1 set f2='hello';
echo select * from t1;
select * from t1;
echo update t1 set f3=10000;
update t1 set f3=10000;

echo select * from t1;
select * from t1;

echo create table t2 (f1 tinyint, f2 float);
create table t2 (f1 tinyint, f2 float);

echo insert into t2 values (112, 235.50);
insert into t2 values (112, 235.50);
echo insert into t2 (f1) values (220);
insert into t2 (f1) values (220);
echo insert into t2 (f2) values (100.50);
insert into t2 (f2) values (100.50);


echo select * from t2;
select * from t2;
echo update t2 set f2=250.50;
update t2 set f2=250.50;
echo update t2 set f1=125;
update t2 set f1=125;

echo select * from t2;
select * from t2;
echo drop table t1;
drop table t1;
echo drop table t2;
drop table t2;
