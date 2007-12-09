echo char datatype LIKE operator testing

create table t1 (f1 char(20), primary key (f1));
insert into t1 values ('TestString');
insert into t1 values ('SearchString');
insert into t1 values ('Dummy');
insert into t1 values ('JustString');
insert into t1 values ('Nothing');
insert into t1 values ('Something');
echo select * from t1;
select * from t1;
select * from t1 where f1 LIKE '%ng';
select * from t1 where f1 LIKE '_e%';
select * from t1 where f1 NOT LIKE '_e%';
select * from t1 where f1 LIKE '%String';
select * from t1 where f1 NOT LIKE '%String';

