echo create table t1 (f1 int,f2 int);
create table t1 (f1 int,f2 int);
echo check for SET AUTOCOMMIT OFF;
SET AUTOCOMMIT OFFer;
echo insert some record;
insert into t1 values(10,20);
insert into t1 values(20,30);
insert into t1 values(30,40);
insert into t1 values(40,50);
insert into t1 values(50,60);
echo rollback;
rollback;
echo select * from t1;
select * from t1;

SET AUTOCOMMIT OFF;
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
insert into t1 values(30,40);
echo test for commit;
commiter;
rollback;
select * from t1;

echo test for rollback;
echo insert 5 records;

insert into t1 values(20,40);
insert into t1 values(20,40);
insert into t1 values(20,40);
insert into t1 values(20,40);
insert into t1 values(20,40);
rollbacked;
commit;
select * from t1;

echo check for show tables;
show tablesss;

echo check for SET AUTOCOMMIT ON;

SET AUTOCOMMIT ONNER;
echo insert some records;

insert into t1 values(50,60);
insert into t1 values(50,60);
insert into t1 values(50,60);
insert into t1 values(50,60);
insert into t1 values(50,60);
rollback;
select * from t1;

echo drop teble;
drop table t1;
