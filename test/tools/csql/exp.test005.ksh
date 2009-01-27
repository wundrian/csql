echo all data type create, insert, select test;
echo create table t1 (f1 char(10), f2 tinyint, f3 smallint,f4 int, f5 bigint,f6 integer, f7 float, f8 real,f9 double,f10 long,f11 binary(128),f12 date,f13 time,f14 timestamp);
Statement Executed
echo insert into t1 values('NIHAR', 1,1,-2147483648,9223372036854775807, 2147483648,1.1, 1000000000.000000,10000001.10000001,99999,'ABCDEF0123456789','2001-1-1', '01:01:01', '2001-11-30 01:01:01');
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	t1.f10	t1.f11	t1.f12	t1.f13	t1.f14	
---------------------------------------------------------
	NIHAR	1	1	-2147483648	9223372036854775807	2147483647	1.100000	1000000000.000000	10000001.100000	99999	ABCDEF0123456789	2001/1/1	1:1:1.0	2001/11/30 1:1:1.0	
	
Statement Executed
