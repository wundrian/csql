echo all data type create, insert, select test;
echo create table t1 (f1 char(10), f2 tinyint, f3 smallint,f4 int, f5 bigint,f6 integer, f7 float, f8 real,f9 double,f10 long,f11 binary(128),f12 date,f13 time,f14 timestamp);
Statement Executed
echo insert into t1 values('CSQL', -128, -32768, -2147483648, -9223372036854775808, -2147483648, -3.4e38, -3.4e38, -1.7e308, -9223372036854775808,'ABCDEF0123456789','00/00/00', '00:00:00', '00-00-00 00:00:00');
Statement Executed: Rows Affected = 1
echo insert into t1 values('NIHAR', 127, 32767, 2147483647, 9223372036854775807, 2147483647, 3.4e38, 3.4e38, 1.7e308, 9223372036854775807,'ABCDEF0123456789','9999/12/31', '23:59:59', '9999/12/31 23:59:59');
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	t1.f10	t1.f11	t1.f12	t1.f13	t1.f14	
---------------------------------------------------------
	CSQL	-128	-32768	-2147483648	-9223372036854775808	-2147483648	-339999995214436424907732413799364296704.000000	-339999999999999996123846586046231871488.000000	-169999999999999993883079578865998174333346074304075874502773119193537729178160565864330091787584707988572262467983188919169916105593357174268369962062473635296474636515660464935663040684957844303524367815028553272712298986386310828644513212353921123253311675499856875650512437415429217994623324794855339589632.000000	-2147483648	ABCDEF0123456789	0/0/0	0:0:0.0	0/0/0 0:0:0.0	
	NIHAR	127	32767	2147483647	9223372036854775807	2147483647	339999995214436424907732413799364296704.000000	339999999999999996123846586046231871488.000000	169999999999999993883079578865998174333346074304075874502773119193537729178160565864330091787584707988572262467983188919169916105593357174268369962062473635296474636515660464935663040684957844303524367815028553272712298986386310828644513212353921123253311675499856875650512437415429217994623324794855339589632.000000	2147483647	ABCDEF0123456789	9999/12/31	23:59:59.0	9999/12/31 23:59:59.0	
	
Statement Executed
