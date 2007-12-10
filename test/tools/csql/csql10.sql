echo Description: SET TRANSACTION type test

create table t1 (f1 int, f2 char(10), f3 int, primary key (f1));
echo check default transaction type
insert into t1 values (10, '20', 10);
insert into t1 values (11, '21', 11);

echo check read only type
set transaction read only;
insert into t1 values (11, '21', 11);
update set t2='a' where f1 = 10;
delete from t1 where f1 = 11;
select * from t1;

echo check read write type
insert into t1 values (50, '50', 50);
update set t2='a' where f1 = 10;
delete from t1 where f1 = 11;
select * from t1;

echo check read only type
set transaction read only;
insert into t1 values (11, '21', 11);
update set t2='a' where f1 = 10;
delete from t1 where f1 = 11;
select * from t1;
