echo all data type create, insert, select test;
create table t1 (f1 int, f2 smallint, f3 char(10),f4 float, f5 double,f6 date, f7 time, f8 timestamp,f9 tinyint,f10 bigint,f11 binary(128),f12 integer,f13 real);
insert into t1 values(1, 1,'NIHAR', 1.1,10000001.10000001, '2001-1-1', '01:01:01', '2001-11-30 01:01:01',1,10000000,'ABCDEF0123456789',2147483647,-123.456);
select * from t1;
drop table t1;
