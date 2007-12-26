echo LIKE operator char datatype testing;

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

echo select * from t1 where f1 LIKE 'UPP%';
select * from t1 where f1 LIKE 'UPP%';

echo select * from t1 where f1 LIKE 'upp%';
select * from t1 where f1 LIKE 'upp%';

echo select * from t1 where f1 LIKE 'upper%letter';
select * from t1 where f1 LIKE 'upp%letter';

echo select * from t1 where f1 LIKE 'upper____letter';
select * from t1 where f1 LIKE 'upp____letter';

drop table t1;
