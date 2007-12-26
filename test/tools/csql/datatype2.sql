echo char datatype testing;

create table t1 (f1 char(20), f2 char(20), primary key (f1));
insert into t1 values ('10', 'A');
insert into t1 values ('11', 'B');
insert into t1 values ('12', 'C');
insert into t1 values ('13', 'D');
insert into t1 values ('14', '14');
insert into t1 values ('50', 'E');
insert into t1 values ('This is really a very big string. should get cut when it is stored', 'E');
insert into t1 values ('UPPERCASE', 'UPPER');
insert into t1 values ('uppercase', 'LOWER');
insert into t1 values ('upperletter', 'LOWER');
insert into t1 values ('uppercaseletter', 'LOWER');
echo select * from t1;
select * from t1;
echo select * from t1 where f1 = '10';
select * from t1 where f1 = '10';
echo select * from t1 where f1 != '12' AND f2 <= '13';
select * from t1 where f1 != '12' AND f2 <= '13';
echo select * from t1 where f1 = '12' AND f2 >= '22';
select * from t1 where f1 = '12' AND f2 >= '22';
echo select * from t1 where f1 = '12' OR  f1 > '13';
select * from t1 where f1 = '12' OR  f1 > '13';
echo select * from t1 where f1 = '12' OR f2 = '13';
select * from t1 where f1 = '12' OR f2 < '13';
echo select * from t1 where f1 = '12' OR f2 < '22';
select * from t1 where f1 = '12' OR f2 <> '22';
echo select * from t1 where NOT f1 = '12';
select * from t1 where NOT f1 = '12';
echo select * from t1 where f1 != '12';
select * from t1 where f1 != '12';
echo select * from t1 where NOT f1 != '12';
select * from t1 where NOT f1 != '12';
echo select * from t1 where f1 = f2;
select * from t1 where f1 = f2;

echo select * from t1 where f2 between 'A' AND 'C';
select * from t1 where f2 between 'A' AND 'C';

echo update t1 set f2 = '2' where f1 != f2;
update t1 set f2 = '2' where f1 != f2;
select * from t1;

echo update t1 set f2 = '3' where f1 = '50';
update t1 set f2 = '3' where f1 = '50';
select * from t1;

delete from t1 where f1 = '50';
select * from t1;
drop table t1;
