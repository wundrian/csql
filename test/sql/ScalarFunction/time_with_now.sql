echo create table t1(f1 int,f2 time);
create table t1(f1 int,f2 time);
echo  insert into t1 values(1,'10:23:2'); 
insert into t1 values(1,'10:23:2');
echo  insert into t1 values(2,'09:12:23');
insert into t1 values(2,'09:12:23');
echo  insert into t1 values(3,'09:18:23');
insert into t1 values(3,'09:18:23');
echo  insert into t1 values(4,'06:23:23');
insert into t1 values(4,'06:23:23');
echo  insert into t1 values(5,now());
insert into t1 values(5,now());
echo  insert into t1 values(6,'05:34:32'); 
insert into t1 values(6,'05:34:32');
echo  insert into t1 values(7,now()); 
insert into t1 values(7,now());
echo  select * from t1; 
select * from t1;
echo  select * from t1 where f2<=now(); 
select * from t1 where f2<=now();
echo  select * from t1 where f2>now(); 
select * from t1 where f2>now();
echo  select * from t1; 
select * from t1;
echo  update t1 set f2=now() where f1<=2; 
update t1 set f2=now() where f1<=2;
echo  select * from t1; 
select * from t1;
echo  update t1 set f2=now(),f1=10 where f2='05:34:32'; 
update t1 set f2=now(),f1=10 where f2='05:34:32';
echo  select * from t1; 
select * from t1;
echo  drop table t1; 
drop table t1;



