echo create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time);
create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time);
echo create index hashtiny on t1(f1) hash;
create index hashtiny on t1(f1) hash;
echo create index hashsmall on t1(f2) hash;
create index hashsmall on t1(f2) hash;
echo create index hashint on t1(f3) hash;
create index hashint on t1(f3) hash;
echo create index hashbig on t1(f4) hash;
create index hashbig on t1(f4) hash;
echo create index hashchar on t1(f5) hash;
create index hashchar on t1(f5) hash;
echo create index hashvarchar on t1(f6) hash;
create index hashvarchar on t1(f6) hash;
echo create index hashdate on t1(f7) hash;
create index hashdate on t1(f7) hash;
echo create index hashtime on t1(f8) hash;
create index hashtime on t1(f8) hash;
insert into t1 values(1,11,111,1111,'CSQL1','Lakshya1','2001-11-12','01:21:00');
insert into t1 values(2,22,222,2222,'CSQL2','Lakshya2','2002-11-12','02:21:00');
insert into t1 values(3,33,333,3333,'CSQL3','Lakshya3','2003-11-12','03:21:00');
insert into t1 values(4,44,444,4444,'CSQL4','Lakshya4','2004-11-12','04:21:00');
insert into t1 values(5,55,555,5555,'CSQL5','Lakshya5','2005-11-12','05:21:00');
echo explain plan select * from t1;  
explain plan select * from t1;  
echo explain plan select * from t1 where f1 = 2;
explain plan select * from t1 where f1 = 2;
echo explain plan select * from t1 where f1 < 3;
explain plan select * from t1 where f1 < 3;
echo explain plan select * from t1 where f2 = 22;
explain plan select * from t1 where f2 = 22;
echo explain plan select * from t1 where f2 > 33;
explain plan select * from t1 where f2 > 33;
echo explain plan select * from t1 where f3 = 333;
explain plan select * from t1 where f3 = 333;
echo explain plan select * from t1 where f3 <> 333;
explain plan select * from t1 where f3 <> 333;
echo explain plan select * from t1 where f4 = 4444;
explain plan select * from t1 where f4 = 4444;
echo explain plan select * from t1 where f4 != 4444;
explain plan select * from t1 where f4 != 4444;
echo explain plan select * from t1 where f5 = 'CSQL3';
explain plan select * from t1 where f5 = 'CSQL3';
echo explain plan select * from t1 where f5 <= 'CSQL3'; 
explain plan select * from t1 where f5 <= 'CSQL3'; 
echo explain plan select * from t1 where f6 = 'Lakshya3';
explain plan select * from t1 where f6 = 'Lakshya3';
echo explain plan select * from t1 where f6 >= 'Lakshya3';
explain plan select * from t1 where f6 >= 'Lakshya3';
echo explain plan select * from t1 where f7 = '2003-11-12';
explain plan select * from t1 where f7 = '2003-11-12';
echo explain plan select * from t1 where f7 > '2003-11-12';
explain plan select * from t1 where f7 > '2003-11-12';
echo explain plan select * from t1 where f8 = '03:21:00';
explain plan select * from t1 where f8 = '03:21:00';
echo explain plan select * from t1 where f8 < '03:21:00';
explain plan select * from t1 where f8 < '03:21:00';