echo all data type create, insert, select test;
echo create table t1 (f1 char(10), f2 tinyint, f3 smallint,f4 int, f5 bigint,f6 integer, f7 float, f8 real,f9 double,f10 long,f11 binary(128),f12 date,f13 time,f14 timestamp);
create table t1 (f1 char(10), f2 tinyint, f3 smallint,f4 int, f5 bigint,f6 integer, f7 float, f8 real,f9 double,f10 long,f11 binary(128),f12 date,f13 time,f14 timestamp);
echo insert into t1 values('CSQL', -128, -32768, -2147483648, -9223372036854775808, -2147483648, -3.4e38, -3.4e38, -1.7e308, -9223372036854775808,'ABCDEF0123456789','00/00/00', '00:00:00', '00-00-00 00:00:00');
insert into t1 values('CSQL', -128, -32768, -2147483648, -9223372036854775808, -2147483648, -3.4e38, -3.4e38, -1.7e308, -9223372036854775808,'ABCDEF0123456789','00/00/00', '00:00:00', '00-00-00 00:00:00');
echo insert into t1 values('NIHAR', 127, 32767, 2147483647, 9223372036854775807, 2147483647, 3.4e38, 3.4e38, 1.7e308, 9223372036854775807,'ABCDEF0123456789','9999/12/31', '23:59:59', '9999/12/31 23:59:59');
insert into t1 values('NIHAR', 127, 32767, 2147483647, 9223372036854775807, 2147483647, 3.4e38, 3.4e38, 1.7e308, 9223372036854775807,'ABCDEF0123456789','9999/12/31', '23:59:59', '9999/12/31 23:59:59');
select * from t1;
drop table t1;
