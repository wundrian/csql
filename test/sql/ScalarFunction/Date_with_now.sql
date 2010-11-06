echo create table t1(f1 int,f2 date);
create table t1(f1 int,f2 date);
echo  insert into t1 values(1,'2003/12/10'); 
insert into t1 values(1,'2003/12/10');
echo  insert into t1 values(2,'2004/12/10');
insert into t1 values(2,'2004/12/10');
echo  insert into t1 values(3,'2005/12/10');
insert into t1 values(3,'2005/12/10');
echo  insert into t1 values(4,'2006/12/10');
insert into t1 values(4,'2006/12/10');
echo  insert into t1 values(5,now());
insert into t1 values(5,now());
echo  insert into t1 values(6,'2007/12/10'); 
insert into t1 values(6,'2007/12/10');
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
echo  update t1 set f2=now(),f1=10 where f2='2007/12/10'; 
update t1 set f2=now(),f1=10 where f2='2007/12/10';
echo  select * from t1; 
select * from t1;
echo  drop table t1; 
drop table t1;



