echo set autocommit off;
set autocommit off;
echo create table t1(f1 int not null,f2 int,f3 int);
create table t1(f1 int not null,f2 int,f3 int);
echo insert into t1 values(1,2,3);
insert into t1 values(1,2,3);
echo insert into t1 values(10,20,30);
insert into t1 values(10,20,30);
echo insert into t1 values(100,200,300);
insert into t1 values(100,200,300);
echo insert into t1 values(1000,2000,3000);
insert into t1 values(1000,2000,3000);
echo commit;
commit;
echo select * from t1;
select * from t1;
echo update t1 set f2=0,f3=f1*0 where f1<=100 and f1 >1;
update t1 set f2=0,f3=f1*0 where f1<=100 and f1 >1;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
