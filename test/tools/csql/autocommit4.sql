echo set autocommit off;
set autocommit off;
echo delete from t1 where f1=1;
delete from t1 where f1=1;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1;
select * from t1;
echo commit;
commit;
echo insert into t1 values(3,'k');
insert into t1 values(3,'k');
echo insert into t1 values(4,'p');
insert into t1 values(4,'p');
echo create table t2(f1 int,f2 char(10));
create table t2(f1 int,f2 char(10));
echo delete from t1 where f1=1;
delete from t1 where f1=1;
echo select * from t1;
select * from t1;
echo rollback;
rollback;

